#include "os-event-handler.hpp"

#include "events/event-dispatcher.hpp"
#include "os-events.hpp"
#include "os.hpp"

#include <GLFW/glfw3.h>
#include <algorithm>


namespace rpg::os {
using events::EventDispatcher;
using namespace events::os;
void OSEventHandler::RegisterHandlers(GLFWwindow* target_window) {
	glfwSetWindowUserPointer(target_window, this);

	glfwGetCursorPos(target_window, &this->mouse_x, &this->mouse_y);

	glfwGetWindowSize(target_window, &this->client_width, &this->client_height);

	glfwSetWindowFocusCallback(target_window, [](GLFWwindow* window, const int focused) {
		OS::focused_window = focused == GL_TRUE ? window : nullptr;
	});

	glfwSetWindowSizeCallback(target_window, [](GLFWwindow* window, auto... args) {
		if (const auto self = static_cast<OSEventHandler*>(glfwGetWindowUserPointer(window))) {
			self->DispatchWindowResizedEvent(args...);
		}
	});

	glfwSetKeyCallback(target_window, [](GLFWwindow* window, auto... args) {
		if (const auto self = static_cast<OSEventHandler*>(glfwGetWindowUserPointer(window))) {
			self->DispatchKeyboardEvent(args...);
		}
	});
	glfwSetCharCallback(target_window, [](GLFWwindow* window, auto... args) {
		if (const auto self = static_cast<OSEventHandler*>(glfwGetWindowUserPointer(window))) {
			self->DispatchCharacterEvent(args...);
		}
	});
	glfwSetCursorPosCallback(target_window, [](GLFWwindow* window, auto... args) {
		if (const auto self = static_cast<OSEventHandler*>(glfwGetWindowUserPointer(window))) {
			self->DispatchMouseMoveEvent(args...);
		}
	});
	glfwSetMouseButtonCallback(target_window, [](GLFWwindow* window, auto... args) {
		if (const auto self = static_cast<OSEventHandler*>(glfwGetWindowUserPointer(window))) {
			self->DispatchMouseButtonEvent(args...);
		}
	});
	glfwSetScrollCallback(target_window, [](GLFWwindow* window, auto... args) {
		if (const auto self = static_cast<OSEventHandler*>(glfwGetWindowUserPointer(window))) {
			self->DispatchMouseScrollEvent(args...);
		}
	});
	glfwSetDropCallback(target_window, [](GLFWwindow* window, auto... args) {
		if (const auto self = static_cast<OSEventHandler*>(glfwGetWindowUserPointer(window))) {
			self->DispatchFileDropEvent(args...);
		}
	});
}

void OSEventHandler::DispatchKeyboardEvent(const int key, const int scancode, const int action, const int mods) const {
	using enum KeyboardEvent::KEY_ACTION;
	const auto key_event = std::make_shared<KeyboardEvent>(KeyboardEvent{key, scancode, KEY_DOWN, mods});
	switch (action) {
	case GLFW_REPEAT: key_event->action = KEY_REPEAT; break;
	case GLFW_RELEASE: key_event->action = KEY_UP; break;
	default:;
	}

	EventDispatcher<KeyboardEvent>::Emit(key_event);
}

void OSEventHandler::DispatchCharacterEvent(const unsigned int uchar) const {
	const auto key_event = std::make_shared<KeyboardEvent>(
			KeyboardEvent{static_cast<const int>(uchar), 0, KeyboardEvent::KEY_ACTION::KEY_CHAR, 0});
	EventDispatcher<KeyboardEvent>::Emit(key_event);
}

void OSEventHandler::DispatchMouseMoveEvent(const double x, const double y) {
	double clamped_x = x, clamped_y = y;
	if (OS::IsMouseLocked()) {
		const double client_center_x = this->client_width / 2.0;
		const double client_center_y = this->client_height / 2.0;
		clamped_x =
				std::clamp(x, (std::min)(this->mouse_x, client_center_x), (std::max)(this->mouse_x, client_center_x));
		clamped_y =
				std::clamp(y, (std::min)(this->mouse_y, client_center_y), (std::max)(this->mouse_y, client_center_y));
	}

	const auto mouse_move_event = std::make_shared<MouseMoveEvent>(MouseMoveEvent{
			x / this->client_width,
			y / this->client_height,
			static_cast<int>(this->mouse_x),
			static_cast<int>(this->mouse_y),
			static_cast<int>(clamped_x),
			static_cast<int>(clamped_y)});
	EventDispatcher<MouseMoveEvent>::Emit(mouse_move_event);

	this->mouse_x = clamped_x;
	this->mouse_y = clamped_y;
}

void OSEventHandler::DispatchMouseScrollEvent(const double x_offset, const double y_offset) const {
	const auto scroll_event = std::make_shared<MouseScrollEvent>(MouseScrollEvent{
			x_offset,
			y_offset,
	});
	EventDispatcher<MouseScrollEvent>::Emit(scroll_event);
}

void OSEventHandler::DispatchMouseButtonEvent(const int button, const int action, const int) const {
	const auto mouse_button_event = std::make_shared<MouseBtnEvent>();
	switch (action) {
		using enum MouseBtnEvent::MOUSE_BTN_ACTION;
	case GLFW_PRESS: mouse_button_event->action = DOWN; break;
	case GLFW_RELEASE: mouse_button_event->action = UP; break;
	default: return;
	}
	switch (button) {
		using enum MouseBtnEvent::MOUSE_BTN;
	case GLFW_MOUSE_BUTTON_LEFT: mouse_button_event->button = LEFT; break;
	case GLFW_MOUSE_BUTTON_RIGHT: mouse_button_event->button = RIGHT; break;
	case GLFW_MOUSE_BUTTON_MIDDLE: mouse_button_event->button = MIDDLE; break;
	default:;
	}
	EventDispatcher<MouseBtnEvent>::Emit(mouse_button_event);
}

void OSEventHandler::DispatchFileDropEvent(const int count, const char** paths) const {
	const auto fd_event = std::make_shared<FileDropEvent>();
	for (int i = 0; i < count; ++i) {
		fd_event->filenames.push_back(paths[i]);
		while (fd_event->filenames[i].find("\\") != std::string::npos) {
			fd_event->filenames[i].replace(fd_event->filenames[i].find("\\"), 1, "/");
		}
	}
	EventDispatcher<FileDropEvent>::Emit(fd_event);
}

void OSEventHandler::DispatchWindowResizedEvent(const int width, const int height) {
	const auto resize_event = std::make_shared<WindowResizedEvent>(
			WindowResizedEvent{this->client_width, this->client_height, width, height});
	EventDispatcher<WindowResizedEvent>::Emit(resize_event);
	this->client_width = width;
	this->client_height = height;
}
} // namespace rpg::os
