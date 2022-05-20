#include "os.hpp"

#include <spdlog/spdlog.h>

#include <algorithm>
#include <iostream>

#include "events.hpp"

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

GLFWwindow* OS::focused_window;
bool OS::mouse_locked = false;

// Error helper function used by GLFW for error messaging.
static void ErrorCallback(int error_no, const char* description) {
	spdlog::get("console_log")->error("[OS] GLFW Error {} : {}", error_no, description);
}

bool OS::InitializeWindow(
		const int width,
		const int height,
		const std::string& title,
		const int glMajor /*= 3*/,
		const int glMinor /*= 3*/,
		bool _fullscreen /*= false*/) {
	this->fullscreen = _fullscreen;
	assert(glMajor >= 3);
	assert(glMajor * 10 + glMinor >= 30);
	glfwSetErrorCallback(ErrorCallback);

	auto l = spdlog::get("console_log");
	// Initialize the library.
	if (glfwInit() != GL_TRUE) {
		l->critical("[OS] Can initialize glfw");
		return false;
	}

	// don't hint much (request default context version)
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);

	// Create a windowed mode window and its OpenGL context.
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glMinor);
	// Enable Core profile if the requested GL version is >= 3.2
	if (glMajor > 3 || (glMajor >= 3 && glMinor >= 2)) {
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}
	glfwWindowHint(GLFW_AUTO_ICONIFY, false); // Don't minimize when a fullscreen window loses focus
	glfwWindowHint(GLFW_SAMPLES, 4); // A basic multi-sampling at the hardware level
	if (_fullscreen) {
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
		// still not right, give up
		glfwTerminate();
		l->critical("[OS] Can't initialize window");
		return false;
	}

	// attach the context
	glfwMakeContextCurrent(this->window);

#ifndef __APPLE__
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		l->critical("[OS] Can initialize glew");
		return false;
	}
#endif

	// check the context version
	std::string glcx_version((char*)glGetString(GL_VERSION));
	int glcx_major = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MAJOR);
	int glcx_minor = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MINOR);
	if (glcx_major < glMajor || (glcx_major == glMajor && glcx_minor < glMinor)) {
		glfwTerminate();
		l->critical(
				"[OS] Initializing OpenGL failed, unsupported version: {} '\n' Press \"Enter\" to "
				"exit\n",
				glcx_version);
		std::cin.get();
		return false;
	}

	const char* glcx_vendor = (char*)glGetString(GL_VENDOR);
	const char* glcx_renderer = (char*)glGetString(GL_RENDERER);
	l->info("{} - {}", glcx_vendor, std::string{glcx_renderer});

	// Check that GLSL is >= 3.30
	std::string glcx_glslver = (char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
	std::string glsl_major = glcx_glslver.substr(0, glcx_glslver.find('.', 0));
	std::string glsl_minor = glcx_glslver.substr(glcx_glslver.find('.', 0) + 1, 1);
	if (glsl_major.at(0) < '3') {
		l->critical(
				"[OS] Initializing OpenGL failed, Shader version must be >= 3.30 : GL version : "
				"{} GLSL version : {} \n Press \"Enter\" to exit\n",
				glcx_version,
				glcx_glslver);
		std::cin.get();
		return false;
	}
	else if (glsl_major.at(0) == '3') {
		if (glsl_minor.at(0) < '3') {
			l->critical(
					"[OS] Initializing OpenGL failed, Shader version must be >= 3.30 : GL version "
					": {} GLSL version : {} \n Press \"Enter\" to exit\n",
					glcx_version,
					glcx_glslver);
			std::cin.get();
			return false;
		}
	}

	l->info("GL version : {} GLSL version : {}", glcx_version, glcx_glslver);

	glfwGetWindowSize(this->window, &this->client_width, &this->client_height);

#ifdef __APPLE__
	// Force retina displays to create a 1x framebuffer so we don't choke our fill rate.
	id cocoaWindow = glfwGetCocoaWindow(this->window);
	id cocoaGLView = ((id(*)(id, SEL))objc_msgSend)(cocoaWindow, sel_getUid("contentView"));
	((void (*)(id, SEL, bool))objc_msgSend)(cocoaGLView, sel_getUid("setWantsBestResolutionOpenGLSurface:"), false);
#endif

	// Getting a list of the avail extensions
	GLint num_exts = 0;
	glGetIntegerv(GL_NUM_EXTENSIONS, &num_exts);
	l->info("Extensions {} : ", num_exts);
	std::string ext("");
	for (GLint e = 0; e < num_exts; e++) {
		ext += "[" + std::string((const char*)glGetStringi(GL_EXTENSIONS, e)) + "] ";
		if (e != 0 && e % 5 == 0) {
			l->debug(ext);
			ext = "";
		}
	}
	l->debug(ext);

	// Associate a pointer for this instance with this window.
	glfwSetWindowUserPointer(this->window, this);
	glfwSetWindowFocusCallback(this->window, &OS::WindowFocusChangeCallback);

	// Set up some callbacks.
	glfwSetWindowSizeCallback(this->window, [](GLFWwindow* _window, auto... args) {
		OS* os = static_cast<OS*>(glfwGetWindowUserPointer(_window));
		if (os) {
			os->UpdateWindowSize(args...);
		}
	});

	glfwSetKeyCallback(this->window, [](GLFWwindow* _window, auto... args) {
		OS* os = static_cast<OS*>(glfwGetWindowUserPointer(_window));
		if (os) {
			os->event_dispatcher.DispatchKeyboardEvent(args...);
		}
	});
	glfwSetCharCallback(this->window, [](GLFWwindow* _window, auto... args) {
		OS* os = static_cast<OS*>(glfwGetWindowUserPointer(_window));
		if (os) {
			os->event_dispatcher.DispatchCharacterEvent(args...);
		}
	});
	glfwSetCursorPosCallback(this->window, [](GLFWwindow* _window, auto... args) {
		OS* os = static_cast<OS*>(glfwGetWindowUserPointer(_window));
		if (os) {
			os->event_dispatcher.DispatchMouseMoveEvent(args..., os->client_width, os->client_height);
		}
	});
	glfwSetMouseButtonCallback(this->window, [](GLFWwindow* _window, auto... args) {
		OS* os = static_cast<OS*>(glfwGetWindowUserPointer(_window));
		if (os) {
			os->event_dispatcher.DispatchMouseButtonEvent(args...);
		}
	});
	glfwSetScrollCallback(this->window, [](GLFWwindow* _window, auto... args) {
		OS* os = static_cast<OS*>(glfwGetWindowUserPointer(_window));
		if (os) {
			os->event_dispatcher.DispatchMouseScrollEvent(args...);
		}
	});
	glfwSetDropCallback(this->window, [](GLFWwindow* _window, auto... args) {
		OS* os = static_cast<OS*>(glfwGetWindowUserPointer(_window));
		if (os) {
			os->event_dispatcher.DispatchFileDropEvent(args...);
		}
	});

	glfwGetCursorPos(this->window, &event_dispatcher.old_mouse_x, &event_dispatcher.old_mouse_y);

	glfwSetInputMode(this->window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

	UpdateWindowSize(width, height);

	OS::focused_window = this->window;
	OS::mouse_locked = false;

	return true;
}

void OS::MakeCurrent() const { glfwMakeContextCurrent(this->window); }

void OS::SetWindowAspectRatio(const int numerator, const int denominator) const {
	glfwSetWindowAspectRatio(this->window, numerator, denominator);
}

GLFWmonitor* get_current_monitor(GLFWwindow* window) {
	int nmonitors, i;
	int wx, wy, ww, wh;
	int mx, my, mw, mh;
	int overlap, bestoverlap;
	GLFWmonitor* bestmonitor;
	GLFWmonitor** monitors;
	const GLFWvidmode* mode;

	bestoverlap = 0;
	bestmonitor = nullptr;

	glfwGetWindowPos(window, &wx, &wy);
	glfwGetWindowSize(window, &ww, &wh);
	monitors = glfwGetMonitors(&nmonitors);

	for (i = 0; i < nmonitors; i++) {
		mode = glfwGetVideoMode(monitors[i]);
		glfwGetMonitorPos(monitors[i], &mx, &my);
		mw = mode->width;
		mh = mode->height;

		overlap = std::max(0, std::min(wx + ww, mx + mw) - std::max(wx, mx))
				  * std::max(0, std::min(wy + wh, my + mh) - std::max(wy, my));

		if (bestoverlap < overlap) {
			bestoverlap = overlap;
			bestmonitor = monitors[i];
		}
	}

	return bestmonitor;
}

void OS::ToggleFullScreen() {
	const auto monitor{get_current_monitor(this->window)};
	if (!this->fullscreen && monitor) {
		this->fullscreen = true;
		const auto mode = glfwGetVideoMode(monitor);
		glfwSetWindowMonitor(this->window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
	}
	else if (monitor) {
		int wx, wy;
		glfwGetWindowPos(window, &wx, &wy);
		const auto mode = glfwGetVideoMode(monitor);
		this->fullscreen = false;
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

void OS::Quit() { glfwSetWindowShouldClose(this->window, true); }

bool OS::Closing() { return glfwWindowShouldClose(this->window) > 0; }

void OS::SwapBuffers() { glfwSwapBuffers(this->window); }

void OS::OSMessageLoop() {
	glfwPollEvents();
	EventQueue<KeyboardEvent>::ProcessEventQueue();
	EventQueue<MouseMoveEvent>::ProcessEventQueue();
	if (this->mouse_lock != OS::mouse_locked) {
		OS::mouse_locked = this->mouse_lock;
		glfwSetInputMode(this->window, GLFW_CURSOR, OS::mouse_locked ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
	}
}

int OS::GetWindowWidth() const { return this->client_width; }

int OS::GetWindowHeight() const { return this->client_height; }

GLFWwindow* OS::GetWindow() { return this->window; }

double OS::GetDeltaTime() {
	double new_time = glfwGetTime();
	double delta_time = new_time - this->last_time;
	this->last_time = new_time;
	return delta_time;
}

double OS::GetTime() { return glfwGetTime(); }


void OS::WindowFocusChangeCallback(GLFWwindow* window, int focused) {
	if (focused == GL_FALSE) {
		OS::focused_window = nullptr;
		if (window != nullptr) {
			// Get the user pointer and cast it.
			OS* os = static_cast<OS*>(glfwGetWindowUserPointer(window));

			if (os) {
			}
		}
	}
	else if (focused == GL_TRUE) {
		OS::focused_window = window;
	}
}

void OS::On(std::shared_ptr<KeyboardEvent> data) {
	if (data->action == KeyboardEvent::KEY_ACTION::KEY_UP && data->key == GLFW_KEY_ENTER && data->mods & GLFW_MOD_ALT) {
		this->ToggleFullScreen();
	}
}

void OS::On(std::shared_ptr<MouseMoveEvent> data) {
	if (OS::mouse_locked) {
		glfwSetCursorPos(this->window, data->old_x, data->old_y);
	}
}

void OS::UpdateWindowSize(const int width, const int height) {
	std::shared_ptr<WindowResizedEvent> resize_event = std::make_shared<WindowResizedEvent>(
			WindowResizedEvent{this->client_width, this->client_height, width, height});
	EventSystem<WindowResizedEvent>::Get()->Emit(resize_event);

	if (!fullscreen) {
		this->client_width = width;
		this->client_height = height;
	}
}

void OS::EnableMouseLock() { this->mouse_lock = true; }

void OS::DisableMouseLock() { this->mouse_lock = false; }

void OS::SetMousePosition(const double x, const double y) { glfwSetCursorPos(OS::focused_window, x, y); }

void OS::GetMousePosition(double* x, double* y) {
	if (focused_window) {
		if (OS::mouse_locked) {
			if (x) {
				*x = 0.5;
			}
			if (y) {
				*y = 0.5;
			}
			return;
		}
		glfwGetCursorPos(OS::focused_window, x, y);
	}
}

} // namespace os
} // namespace rpg
