#pragma once

#ifndef __APPLE__
#include <GL/glew.h>
#endif

#ifdef WIN32
#include <GL/wglew.h>
#endif

#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#endif
#include <GLFW/glfw3.h>

#include "os-event-handler.hpp"

#include "constants.hpp"
#include "events/event-queue.hpp"
#include "util/nomovenocopy.hpp"

namespace rpg {
namespace events::os {
struct MouseLockEvent;
struct KeyboardEvent;
struct MouseMoveEvent;
struct WindowResizedEvent;
} // namespace events::os

using events::EventQueue;
using namespace events::os;

namespace os {
class OS final :
		public EventQueue<KeyboardEvent>,
		public EventQueue<MouseMoveEvent>,
		public EventQueue<MouseLockEvent>,
		public EventQueue<WindowResizedEvent>,
		public util::NoMoveNoCopy {
public:
	/**
	 * @brief Initialize the rendering window and makes the window's context the current one.
	 *
	 * @param[in] width The window's client width
	 * @param[in] height The window's client height
	 * @param[in] title The title to show in the title bar and task manager.
	 * @param[in] requested_gl_version OpenGL major version number. Must be >= OpenGL 3.3
	 * @param[in] start_fullscreen Whether the window should be started in fullscreen mode.
	 * @return If creation was successful or not.
	 */
	bool InitializeWindow(
			int width,
			int height,
			const std::string& title,
			config::GL_VERSION_PAIR requested_gl_version = config::PREFERRED_GL_VERSION,
			bool start_fullscreen = false);

	/** @brief Make the context of the window current for the calling thread
	 *
	 */
	void MakeCurrent() const;

	/** @brief Sets the desired window aspect ratio numerator:denominator e.g. 16:9, 4:3
	 *
	 */
	void SetWindowAspectRatio(int numerator = 16, int denominator = 9) const;

	/** @brief Toggles between fullscreen and windowed mode based.
	 *
	 */
	void ToggleFullScreen() const;

	/** @brief Detach the context of the window from the calling thread
	 *
	 */
	static void DetachContext();

	/**
	 * @brief Calls GLFWTerminate to close the window.
	 *
	 * This is a static method so it can be called from anywhere to terminate the current
	 * window.
	 */
	static void Terminate();

	/**
	 * @brief Tells the OS that the active window should close.
	 *
	 * Since the main loop is based on that close status of that active window
	 * this effectively causes Closing() to return true during an upcoming message loop.
	 */
	void Quit() const;

	/**
	 * @brief Checks if the window is closing.
	 *
	 * @return True if the window is closing.
	 */
	bool Closing() const;

	/**
	 * @brief Swap the front and back buffers. Call after rendering.
	 * If V-SYNC is on, this will block for swap interval.
	 *
	 */
	void SwapBuffers() const;

	/**
	 * @brief Returns the refresh rate that active window is on.
	 *
	 * @return The monitor's refresh rate.
	 */
	int GetMonitorRefreshRate() const;

	/**
	 * @brief Processes events in the OS message event loop.
	 *
	 */
	void OSMessageLoop();

	/**
	 * @brief Gets the cached window width.
	 *
	 * @return The window width.
	 */
	int GetWindowWidth() const;

	/**
	 * @brief Gets the cached window height.
	 *
	 * @return The window height.
	 */
	int GetWindowHeight() const;

	/**
	 * @brief Returns the time since the last call.
	 *
	 * @return The amount of time that have passed since the last call in seconds.
	 */
	double GetDeltaTime();

	/**
	 * @brief Returns the time since initialization from glfw.
	 *
	 * @return The amount of time since glfw was initialized in seconds.
	 */
	static double GetTime();

	/**
	 * @brief Returns the current active window.
	 *
	 * @return The current active window.
	 */
	GLFWwindow* GetWindow() const;

	/**
	 * @brief Sets the mouse cursor position relative to the upper-left corner of the window.
	 *
	 * @param[in] x The new x coordinate of the mouse in screen coordinates.
	 * @param[in] y The new y coordinate of the mouse in screen coordinates.
	 */
	static void SetMousePosition(double x, double y);

	/**
	 * @brief Gets the mouse cursor position relative to the upper-left corner of the window.
	 *
	 * @param[out] x The current x coordinate of the mouse in screen coordinates.
	 * @param[out] y The current y coordinate of the mouse in screen coordinates.
	 */
	static void GetMousePosition(double* x, double* y);

	inline static GLFWwindow* focused_window{nullptr}; // The window that currently has focus.

	static bool IsMouseLocked() { return mouse_locked; }

private:
	OSEventHandler event_handler;

	using EventQueue<KeyboardEvent>::On;
	/**
	 * @brief Keyboard event listener, useful for events such as alt-enter to toggle fullscreen.
	 *
	 * @param[in] data Keyboard event data
	 */
	void On(std::shared_ptr<KeyboardEvent> data) override;

	using EventQueue<MouseMoveEvent>::On;
	/**
	 * @brief Mouse move event listener
	 *
	 * @param[in] data Keyboard event data
	 */
	void On(std::shared_ptr<MouseMoveEvent> data) override;
	using EventQueue<MouseLockEvent>::On;
	/**
	 * @brief Mouse lock event listener
	 *
	 * @param[in] data Keyboard event data
	 */
	void On(std::shared_ptr<MouseLockEvent> data) override;

	using EventQueue<WindowResizedEvent>::On;
	/**
	 * @brief Mouse lock event listener
	 *
	 * @param[in] data Window resized event data
	 */
	void On(std::shared_ptr<WindowResizedEvent> data) override;

	GLFWwindow* window{nullptr};
	int client_width{0}, client_height{0}; // Current window's client width and height.
	double last_time{0}; // The time at the last call to GetDeltaTime().
	inline static bool mouse_locked{false}; // If mouse lock is locked, e.g. for mouse look in an FPS.
	inline static bool fullscreen{false}; // False if the game is in windowed mode
};
} // namespace os
} // namespace rpg
