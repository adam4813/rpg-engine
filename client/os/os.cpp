#include "os.hpp"

#include <spdlog/spdlog.h>

#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>

#include "os-events.hpp"

#ifdef __APPLE__
// Needed so we can disable retina support for our window.
#define GLFW_EXPOSE_NATIVE_COCOA 1
#define GLFW_EXPOSE_NATIVE_NSGL 1
#include <GLFW/glfw3native.h>
// We can't just include objc/runtime.h and objc/message.h because glfw is too forward thinking for its own good.
typedef void* SEL;
extern "C" id objc_msgSend(id self, SEL op, ...);
extern "C" SEL sel_getUid(const char* str);
#endif


namespace rpg {
namespace os {
// Error helper function used by GLFW for error messaging.
static void ErrorCallback(int error_no, const char* description) {
	spdlog::get("console_log")->error("[OS] GLFW Error {} : {}", error_no, description);
}

bool OS::InitializeWindow(
		const int width,
		const int height,
		const std::string& title,
		config::GL_VERSION_PAIR requested_gl_version,
		const bool start_fullscreen /*= false*/) {
	fullscreen = start_fullscreen;
	assert(requested_gl_version.major >= 3);
	assert(requested_gl_version.major * 10 + requested_gl_version.minor >= 30);
	glfwSetErrorCallback(ErrorCallback);

	auto l = spdlog::get("console_log");
	// Initialize the library.
	if (glfwInit() != GL_TRUE) {
		l->critical("[OS] Can initialize glfw");
		return false;
	}

	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, requested_gl_version.major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, requested_gl_version.minor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_AUTO_ICONIFY, false); // Don't minimize when a fullscreen window loses focus
	glfwWindowHint(GLFW_SAMPLES, 4); // A basic multi-sampling at the hardware level

	if (fullscreen) {
		const auto monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		glfwWindowHint(GLFW_RED_BITS, mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
		this->window = glfwCreateWindow(mode->width, mode->height, title.c_str(), monitor, nullptr);
	}
	else {
		this->window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	}

	if (!this->window) {
		glfwTerminate();
		l->critical("[OS] Can't initialize window");
		return false;
	}

	glfwMakeContextCurrent(this->window);

#ifndef __APPLE__
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		l->critical("[OS] Can initialize glew");
		return false;
	}
#endif

	// Check that GLSL is >= requested context version
	const std::string gl_version(reinterpret_cast<const char*>(glGetString(GL_VERSION)));
	const std::string glsl_version{reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION))};
	const auto glsl_major = std::stoi(glsl_version.substr(0, glsl_version.find('.', 0)));
	const auto glsl_minor = std::stoi(glsl_version.substr(glsl_version.find('.', 0) + 1, 1));
	if (glsl_major < requested_gl_version.major
		|| (glsl_major == requested_gl_version.major && glsl_minor < requested_gl_version.minor)) {
		l->critical(
				"[OS] Initializing OpenGL failed, Shader version must be >= {}.{}0 : GLSL version : {} \n Press "
				"\"Enter\" to exit\n",
				requested_gl_version.major,
				requested_gl_version.minor,
				glsl_version);
		std::cin.get();
		return false;
	}

	l->info("{} - {}",
			reinterpret_cast<const char*>(glGetString(GL_VENDOR)),
			reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
	l->info("GL version : {} GLSL version : {}", gl_version, glsl_version);

#ifdef __APPLE__
	// Force retina displays to create a 1x framebuffer so we don't choke our fill rate.
	id cocoaWindow = glfwGetCocoaWindow(this->window);
	id cocoaGLView = ((id(*)(id, SEL))objc_msgSend)(cocoaWindow, sel_getUid("contentView"));
	((void (*)(id, SEL, bool))objc_msgSend)(cocoaGLView, sel_getUid("setWantsBestResolutionOpenGLSurface:"), false);
#endif

	// Getting a list of the avail extensions
	GLint num_extensions = 0;
	glGetIntegerv(GL_NUM_EXTENSIONS, &num_extensions);
	l->info("Extensions - {}", num_extensions);
	std::string ext("");
	for (GLint e = 0; e < num_extensions; e++) {
		ext += "[" + std::string(reinterpret_cast<const char*>(glGetStringi(GL_EXTENSIONS, e))) + "] ";
		if (e != 0 && e % 5 == 0) {
			l->debug(ext);
			ext = "";
		}
	}
	l->debug(ext);

	this->event_handler.RegisterHandlers(window);

	glfwGetWindowSize(this->window, &this->client_width, &this->client_height);

	glfwSetInputMode(this->window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

	focused_window = this->window;
	mouse_locked = false;

	return true;
}

void OS::MakeCurrent() const { glfwMakeContextCurrent(this->window); }

void OS::SetWindowAspectRatio(const int numerator, const int denominator) const {
	glfwSetWindowAspectRatio(this->window, numerator, denominator);
}

GLFWmonitor* GetCurrentMonitor(GLFWwindow* window) {
	int wx, wy, ww, wh;
	int mx, my;

	glfwGetWindowPos(window, &wx, &wy);
	glfwGetWindowSize(window, &ww, &wh);
	int num_monitors;
	GLFWmonitor** monitors = glfwGetMonitors(&num_monitors);

	int best_overlap = 0;
	GLFWmonitor* best_monitor = nullptr;
	for (int i = 0; i < num_monitors; i++) {
		const GLFWvidmode* mode = glfwGetVideoMode(monitors[i]);
		glfwGetMonitorPos(monitors[i], &mx, &my);
		const int mw = mode->width;
		const int mh = mode->height;

		if (const int overlap = (std::max)(0, (std::min)(wx + ww, mx + mw) - std::max(wx, mx))
								* (std::max)(0, (std::min)(wy + wh, my + mh) - std::max(wy, my));
			best_overlap < overlap) {
			best_overlap = overlap;
			best_monitor = monitors[i];
		}
	}

	return best_monitor;
}

void OS::ToggleFullScreen() const {
	if (const auto monitor{GetCurrentMonitor(this->window)}; !fullscreen && monitor) {
		fullscreen = true;
		const auto mode = glfwGetVideoMode(monitor);
		glfwSetWindowMonitor(this->window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
	}
	else if (monitor) {
		int wx, wy;
		glfwGetWindowPos(window, &wx, &wy);
		const auto mode = glfwGetVideoMode(monitor);
		fullscreen = false;
		glfwSetWindowMonitor(
				this->window,
				nullptr,
				wx + mode->width / 2
						- this->client_width / 2, // Position window in center of monitor it was fullscreen on
				wy + mode->height / 2
						- this->client_height / 2, // Position window in center of monitor it was fullscreen on
				this->client_width,
				this->client_height,
				GLFW_DONT_CARE);
	}
}

void OS::DetachContext() { glfwMakeContextCurrent(nullptr); }

void OS::Terminate() { glfwTerminate(); }

void OS::Quit() const { glfwSetWindowShouldClose(this->window, true); }

bool OS::Closing() const { return glfwWindowShouldClose(this->window) > 0; }

void OS::SwapBuffers() const { glfwSwapBuffers(this->window); }

void OS::OSMessageLoop() {
	glfwPollEvents();
	EventQueue<KeyboardEvent>::ProcessEventQueue();
	EventQueue<MouseMoveEvent>::ProcessEventQueue();
	EventQueue<MouseLockEvent>::ProcessEventQueue();
	EventQueue<WindowResizedEvent>::ProcessEventQueue();
}

int OS::GetWindowWidth() const { return this->client_width; }

int OS::GetWindowHeight() const { return this->client_height; }

GLFWwindow* OS::GetWindow() const { return this->window; }

double OS::GetDeltaTime() {
	const double new_time = glfwGetTime();
	const double delta_time = new_time - this->last_time;
	this->last_time = new_time;
	return delta_time;
}

double OS::GetTime() { return glfwGetTime(); }

void OS::On(const std::shared_ptr<KeyboardEvent> data) {
	if (data->action == KeyboardEvent::KEY_ACTION::KEY_UP && data->key == GLFW_KEY_ENTER && data->mods & GLFW_MOD_ALT) {
		this->ToggleFullScreen();
	}
}

void OS::On(const std::shared_ptr<MouseMoveEvent> data) {
	if (mouse_locked) {
		glfwSetCursorPos(this->window, data->old_x, data->old_y);
	}
}

void OS::On(const std::shared_ptr<MouseLockEvent> data) {
	this->mouse_locked = data->lock;
	glfwSetInputMode(this->window, GLFW_CURSOR, this->mouse_locked ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}

void OS::On(const std::shared_ptr<WindowResizedEvent> data) {
	if (!fullscreen) {
		this->client_width = data->new_width;
		this->client_height = data->new_height;
	}
}

void OS::SetMousePosition(const double x, const double y) { glfwSetCursorPos(focused_window, x, y); }

void OS::GetMousePosition(double* x, double* y) {
	if (focused_window) {
		if (mouse_locked) {
			if (x) {
				*x = 0.5;
			}
			if (y) {
				*y = 0.5;
			}
			return;
		}
		glfwGetCursorPos(focused_window, x, y);
	}
}

} // namespace os
} // namespace rpg
