#pragma once

#ifndef __APPLE__
#include <gl/glew.h>
#endif

#ifdef WIN32
#include <gl/wglew.h>
#endif

#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#endif
#include <GLFW/glfw3.h>

#include <chrono>

#include "event-system.hpp"
#include "os-event-dispatcher.hpp"

namespace rpg {
struct KeyboardEvent;
struct MouseMoveEvent;
namespace os {

class OS final : public EventQueue<KeyboardEvent>, public EventQueue<MouseMoveEvent> {
public:
	/**
	* \brief Initialize the rendering window and makes the window's context the current one.
	*
	* \param[in] const unsigned int width, height The window's client width and height
	* \param[in] const std::string title The title to show in the title bar and task manager.
	* \param[in] const glMajor OpenGL major version number. Must be >= 3
	* \param[in] const glMinor OpenGL minor version. If major = 3, must be 3 (OpenGL 3.3)
	* \param[in] bool fullscreen Whether the window should be started in fullscreen mode.
	* \return bool If creation was successful or not.
	*/
	bool InitializeWindow(
			int width,
			int height,
			const std::string& title,
			int glMajor = 3,
			int glMinor = 3,
			bool fullscreen = false);

	/** \brief Make the context of the window current for the calling thread
	*
	*/
	void MakeCurrent() const;

	/** \brief Sets the desired window aspect ratio numerator:denominator e.g. 16:9, 4:3
	*
	*/
	void SetWindowAspectRatio(const int numerator = 16, const int denominator = 9) const;

	/** \brief Toggles between fullscreen and windowed mode based.
	*
	*/
	void ToggleFullScreen();

	/** \brief Detach the context of the window from the calling thread
	*
	*/
	void DetachContext();

	/**
	* \brief Calls GLFWTerminate to close the window.
	*
	* This is a static method so it can be called from anywhere to terminate the current
	* window.
	*/
	static void Terminate();

	/**
	* \brief Tells the OS that the active window should close.
	*
	* Since the main loop is based on that close status of that active window
	* this effectively causes Closing() to return true during an upcoming message loop.
	*/
	void Quit();

	/**
	* \brief Checks if the window is closing.
	*
	* \return bool True if the window is closing.
	*/
	bool Closing();

	/**
	* \brief Swap the front and back buffers. Call after rendering.
	*/
	void SwapBuffers();

	/**
	* \brief Processes events in the OS message event loop.
	*
	*/
	void OSMessageLoop();

	/**
	* \brief Gets the cached window width.
	*
	* \return int The window width.
	*/
	int GetWindowWidth() const;

	/**
	* \brief Gets the cached window height.
	*
	* \return int The window height.
	*/
	int GetWindowHeight() const;

	/**
	* \brief Returns the time since the start of the program.
	*
	* \return double The amount of time that have passed since the last call in seconds.
	*/
	double GetDeltaTime();

	/**
	* \brief Returns the time since initialization from glfw.
	*
	* \return double The amount of time since glfw was initialized in seconds.
	*/
	double GetTime();

	/**
	* \brief Returns the current active window.
	*
	* \return GLFWwindow* The current active window.
	*/
	GLFWwindow* GetWindow();


	/**
	* \brief Callback for window focus change events.
	*
	* \param[in] GLFWwindow* window
	* \param[in] int focused GL_TRUE if focused, GL_FALSE if unfocused.
	* \return void
	*/
	static void WindowFocusChangeCallback(GLFWwindow* window, int focused);

	void EnableMouseLock();

	void DisableMouseLock();

	/**
	* \brief Sets the mouse cursor position relative to the upper-left corner of the window.
	*
	* \param[in] double x, y The new x and y coordinate of the mouse in screen coordinates.
	* \return void
	*/
	static void SetMousePosition(double x, double y);

	/**
	* \brief Gets the mouse cursor position relative to the upper-left corner of the window.
	*
	* \param[out] double* x, y The current x and y coordinate of the mouse in screen coordinates.
	* \return void
	*/
	static void GetMousePosition(double* x, double* y);

	static const GLFWwindow* GetFocusedWindow() { return OS::focused_window; }

private:
	friend class OsEventDispatcher;
	OsEventDispatcher event_dispatcher;

	/**
	* \brief Keyboard event listener, useful for events such as alt-enter to toggle fullscreen.
	*
	* \param[in] std::shared_ptr<KeyboardEvent> data Keyboard event data
	*/
	using EventQueue<KeyboardEvent>::On;
	void On(std::shared_ptr<KeyboardEvent> data);
	/**
	* \brief Mouse move event listener, used to handle mouse lock
	*
	* \param[in] std::shared_ptr<MouseMoveEvent> data Keyboard event data
	*/
	using EventQueue<MouseMoveEvent>::On;
	void On(std::shared_ptr<MouseMoveEvent> data);

	/**
	* \brief Updates the internal size variables from the windowResized callback.
	*
	* \param[in] const int width, height The new client width and height of the window
	*/
	void UpdateWindowSize(const int width, const int height);


	GLFWwindow* window{nullptr};
	static GLFWwindow* focused_window; // The window that currently has focus.
	int client_width{0}, client_height{0}; // Current window's client width and height.
	double last_time{0}; // The time at the last call to GetDeltaTime().
	bool mouse_lock{false}; // If mouse lock is requested.
	static bool mouse_locked; // If mouse lock is enabled causing the cursor to snap to
			// mid-window each movement event.
	bool fullscreen{false}; // False if the game is in windowed mode
};
} // namespace os
} // namespace rpg
