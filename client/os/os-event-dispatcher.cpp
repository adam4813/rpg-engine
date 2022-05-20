#include "os-event-dispatcher.hpp"

#include "event-system.hpp"
#include "events.hpp"
#include "os.hpp"

#include <GLFW/glfw3.h>
#include <algorithm>

namespace rpg {
namespace os {

void OsEventDispatcher::DispatchKeyboardEvent(const int key, const int scancode, const int action, const int mods) const {
	using enum KeyboardEvent::KEY_ACTION;
	const auto key_event =
			std::make_shared<KeyboardEvent>(KeyboardEvent{key, scancode, KEY_DOWN, mods});
	switch (action) {
	case GLFW_REPEAT: key_event->action = KEY_REPEAT; break;
	case GLFW_RELEASE: key_event->action = KEY_UP; break;
	default: ;
	}

	EventSystem<KeyboardEvent>::Get()->Emit(key_event);
}

void OsEventDispatcher::DispatchCharacterEvent(const unsigned int uchar) const {
	const auto key_event =
			std::make_shared<KeyboardEvent>(KeyboardEvent{(const int)uchar, 0, KeyboardEvent::KEY_ACTION::KEY_CHAR, 0});
	EventSystem<KeyboardEvent>::Get()->Emit(key_event);
}

void OsEventDispatcher::DispatchMouseMoveEvent(const double x, const double y, const int client_width, const int client_height) {
	if (OS::mouse_locked) {
		const double client_center_x = client_width / 2.0;
		const double client_center_y = client_height / 2.0;
		this->old_mouse_x = std::clamp(
				x, (std::min)(this->old_mouse_x, client_center_x), (std::max)(this->old_mouse_x, client_center_x));
		this->old_mouse_y = std::clamp(
				y, (std::min)(this->old_mouse_y, client_center_y), (std::max)(this->old_mouse_y, client_center_y));
	}
	else {
		this->old_mouse_x = x;
		this->old_mouse_y = y;
	}
	const auto mouse_move_event = std::make_shared<MouseMoveEvent>(MouseMoveEvent{
			x / client_width,
			y / client_height,
			static_cast<int>(this->old_mouse_x),
			static_cast<int>(this->old_mouse_y),
			static_cast<int>(x),
			static_cast<int>(y)});
	EventSystem<MouseMoveEvent>::Get()->Emit(mouse_move_event);
}

void OsEventDispatcher::DispatchMouseScrollEvent(const double xoffset, const double yoffset) const {
	const auto scroll_event = std::make_shared<MouseScrollEvent>(MouseScrollEvent{
			xoffset,
			yoffset,
	});
	EventSystem<MouseScrollEvent>::Get()->Emit(scroll_event);
}

void OsEventDispatcher::DispatchMouseButtonEvent(const int button, const int action, const int) const {
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
	default: ;
	}
	EventSystem<MouseBtnEvent>::Get()->Emit(mouse_button_event);
}

void OsEventDispatcher::DispatchFileDropEvent(const int count, const char** paths) const {
	const auto fd_event = std::make_shared<FileDropEvent>();
	for (int i = 0; i < count; ++i) {
		fd_event->filenames.push_back(paths[i]);
		while (fd_event->filenames[i].find("\\") != std::string::npos) {
			fd_event->filenames[i].replace(fd_event->filenames[i].find("\\"), 1, "/");
		}
	}
	EventSystem<FileDropEvent>::Get()->Emit(fd_event);
}
} // namespace os
} // namespace rpg
