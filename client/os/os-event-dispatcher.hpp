#pragma once

namespace rpg {
namespace os {

// TODO: Collect all events during set window to all creating a snapshot of events.

class OsEventDispatcher {
public:
	/**
	* \brief Dispatches keyboard events from the callback.
	*
	* \param[in] const int key ASCII key number.
	* \param[in] const int scancode The converted key value
	* \param[in] const int action The event type.
	* \param[in] const int mods Modifier keys.
	* \return void
	*/
	void DispatchKeyboardEvent(int key, int scancode, int action, int mods) const;

	/**
	* \brief Dispatches a character event.
	*
	* \param[in] const unsigned int uchar The Unicode character key code.
	* \return void
	*/
	void DispatchCharacterEvent(unsigned int uchar) const;

	/**
	* \brief Dispatches mouse movement events.
	*
	* It determines the changes in mouse position and stores the new position for later.
	* \param[in] const double x, y The new x and y coordinate of the mouse in screen coordinates.
	* \param[in] const int client_width, client_height Client width and height window the mouse moved over.
	* \return void
	*/
	void DispatchMouseMoveEvent(double x, double y, int client_width, int client_height);

	/**
	* \brief Dispatches mouse scroll events.
	*
	* It determines the changes in mouse position and stores the new position for later.
	* \param[in] const double xoffset, yoffset The delta x and y coordinate of the mouse wheel.
	* \return void
	*/
	void DispatchMouseScrollEvent(double xoffset, double yoffset) const;

	/**
	* \brief Dispatches mouse button events from the callback.
	*
	* \param[in] const int button The button that the action occurred on.
	* \param[in] const int action The action that occurred.
	* \param[in] const int mods Modifier keys.
	* \return void
	*/
	void DispatchMouseButtonEvent(int button, int action, int mods) const;

	/**
	* \brief Dispatches a character event.
	*
	* \param[in] const int count The number of files dropped.
	* \param[in] const char** paths Array of filenames.
	* \return void
	*/
	void DispatchFileDropEvent(int count, const char** paths) const;

private:
	friend class OS;
	double old_mouse_x{0}, old_mouse_y{0};
};
} // namespace os
} // namespace rpg
