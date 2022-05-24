#pragma once

#include "util/types.hpp"
#include <glm/glm.hpp>
#include <string>
#include <vector>

namespace rpg::events::os {

struct MouseHover {
	glm::vec3 ray_hit_point_world;
};

struct KeyboardEvent {
	enum class KEY_ACTION { KEY_DOWN, KEY_UP, KEY_REPEAT, KEY_CHAR };
	int key{0};
	int scancode{0};
	KEY_ACTION action{KEY_ACTION::KEY_DOWN};
	int mods{0};
};

struct MouseBtnEvent {
	enum class MOUSE_BTN_ACTION { DOWN, UP, UNKNOWN };
	enum class MOUSE_BTN { LEFT, RIGHT, MIDDLE };
	MOUSE_BTN_ACTION action = MOUSE_BTN_ACTION::UNKNOWN;
	MOUSE_BTN button = MOUSE_BTN::LEFT;
};

/** Mouse change of position event */
struct MouseMoveEvent {
	double norm_x{0.0}, norm_y{0.0}; /// Resolution independent new x, y (0-1) from upper-left to lower-right.
	int old_x{0}, old_y{0}; /// Client space old x, y.
	int new_x{0}, new_y{0}; /// Client space new x, y.
};

/** Mouse wheel event */
struct MouseScrollEvent {
	double x_offset{0.0}, y_offset{0.0}; /// Delta x, y of mouse wheel.
};

struct MouseLockEvent {
	bool lock{false};
};

struct MouseClickEvent {
	eid entity_id{0};
	MouseBtnEvent::MOUSE_BTN button;
	glm::vec3 ray_hit_point_world{0.f, 0.f, 0.f};
	double ray_distance;
};

struct WindowResizedEvent {
	int old_width{0}, old_height{0}; // Client space old width, height.
	int new_width{0}, new_height{0}; // Client space new width, height.
};

struct FileDropEvent {
	std::vector<std::string> filenames;
};

} // namespace rpg::events::os
