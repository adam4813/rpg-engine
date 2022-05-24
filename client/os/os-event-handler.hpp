#pragma once
struct GLFWwindow;

namespace rpg::os {

class OSEventHandler {
public:
	void RegisterHandlers(GLFWwindow* target_window);

	/**
	* @brief Dispatches keyboard events from the callback.
	*
	* @param[in] key ASCII key number.
	* @param[in] scancode The converted key value
	* @param[in] action The event type.
	* @param[in] mods Modifier keys.
	*/
	void DispatchKeyboardEvent(int key, int scancode, int action, int mods) const;

	/**
	* @brief Dispatches a character event.
	*
	* @param[in] uchar The Unicode character key code.
	*/
	void DispatchCharacterEvent(unsigned int uchar) const;

	/**
	* @brief Dispatches mouse movement events.
	*
	* It determines the changes in mouse position and stores the new position for later.
	* @param[in] x The new x coordinate of the mouse in screen coordinates.
	* @param[in] y The new y coordinate of the mouse in screen coordinates.
	*/
	void DispatchMouseMoveEvent(double x, double y);

	/**
	* @brief Dispatches mouse scroll events.
	*
	* It determines the changes in mouse position and stores the new position for later.
	* @param[in] x_offset The delta x coordinate of the mouse wheel
	* @param[in] y_offset The delta y coordinate of the mouse wheel.
	*/
	void DispatchMouseScrollEvent(double x_offset, double y_offset) const;

	/**
	* @brief Dispatches mouse button events from the callback.
	*
	* @param[in] button The button that the action occurred on.
	* @param[in] action The action that occurred.
	* @param[in] mods Modifier keys.
	*/
	void DispatchMouseButtonEvent(int button, int action, int mods) const;

	/**
	* @brief Dispatches a character event.
	*
	* @param[in] count The number of files dropped.
	* @param[in] paths Array of filenames.
	*/
	void DispatchFileDropEvent(int count, const char** paths) const;

	/**
	* @brief Dispatches a window resized event.
	*
	* @param[in] width The client window width.
	* @param[in] height The client window height.
	*/
	void DispatchWindowResizedEvent(int width, int height);

private:
	// Cache to send with events that change them
	double mouse_x{0}, mouse_y{0};
	int client_width{0}, client_height{0};
};
} // namespace rpg::os
