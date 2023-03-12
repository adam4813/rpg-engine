---
title: rpg::os::OS

---

# rpg::os::OS





Inherits from [rpg::events::EventQueue< KeyboardEvent >](/engine/Classes/classrpg_1_1events_1_1_event_queue/), [rpg::events::EventQueue< MouseMoveEvent >](/engine/Classes/classrpg_1_1events_1_1_event_queue/), [rpg::events::EventQueue< MouseLockEvent >](/engine/Classes/classrpg_1_1events_1_1_event_queue/), [rpg::events::EventQueue< WindowResizedEvent >](/engine/Classes/classrpg_1_1events_1_1_event_queue/), [rpg::util::NoMoveNoCopy](/engine/Classes/classrpg_1_1util_1_1_no_move_no_copy/)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| bool | **[InitializeWindow](/engine/Classes/classrpg_1_1os_1_1_o_s/#function-initializewindow)**(int width, int height, const std::string & title, [config::GL_VERSION_PAIR](/engine/Classes/structrpg_1_1config_1_1_g_l___v_e_r_s_i_o_n___p_a_i_r/) requested_gl_version =config::PREFERRED_GL_VERSION, bool start_fullscreen =false)<br>Initialize the rendering window and makes the window's context the current one.  |
| void | **[MakeCurrent](/engine/Classes/classrpg_1_1os_1_1_o_s/#function-makecurrent)**() const<br>Make the context of the window current for the calling thread.  |
| void | **[SetWindowAspectRatio](/engine/Classes/classrpg_1_1os_1_1_o_s/#function-setwindowaspectratio)**(int numerator =16, int denominator =9) const<br>Sets the desired window aspect ratio numerator:denominator e.g. 16:9, 4:3.  |
| void | **[ToggleFullScreen](/engine/Classes/classrpg_1_1os_1_1_o_s/#function-togglefullscreen)**() const<br>Toggles between fullscreen and windowed mode based.  |
| void | **[Quit](/engine/Classes/classrpg_1_1os_1_1_o_s/#function-quit)**() const<br>Tells the [OS](/engine/Classes/classrpg_1_1os_1_1_o_s/) that the active window should close.  |
| bool | **[Closing](/engine/Classes/classrpg_1_1os_1_1_o_s/#function-closing)**() const<br>Checks if the window is closing.  |
| void | **[SwapBuffers](/engine/Classes/classrpg_1_1os_1_1_o_s/#function-swapbuffers)**() const<br>Swap the front and back buffers. Call after rendering. If V-SYNC is on, this will block for swap interval.  |
| int | **[GetMonitorRefreshRate](/engine/Classes/classrpg_1_1os_1_1_o_s/#function-getmonitorrefreshrate)**() const<br>Returns the refresh rate that active window is on.  |
| void | **[OSMessageLoop](/engine/Classes/classrpg_1_1os_1_1_o_s/#function-osmessageloop)**()<br>Processes events in the [OS](/engine/Classes/classrpg_1_1os_1_1_o_s/) message event loop.  |
| int | **[GetWindowWidth](/engine/Classes/classrpg_1_1os_1_1_o_s/#function-getwindowwidth)**() const<br>Gets the cached window width.  |
| int | **[GetWindowHeight](/engine/Classes/classrpg_1_1os_1_1_o_s/#function-getwindowheight)**() const<br>Gets the cached window height.  |
| double | **[GetDeltaTime](/engine/Classes/classrpg_1_1os_1_1_o_s/#function-getdeltatime)**()<br>Returns the time since the last call.  |
| GLFWwindow * | **[GetWindow](/engine/Classes/classrpg_1_1os_1_1_o_s/#function-getwindow)**() const<br>Returns the current active window.  |
| void | **[DetachContext](/engine/Classes/classrpg_1_1os_1_1_o_s/#function-detachcontext)**()<br>Detach the context of the window from the calling thread.  |
| void | **[Terminate](/engine/Classes/classrpg_1_1os_1_1_o_s/#function-terminate)**()<br>Calls GLFWTerminate to close the window.  |
| double | **[GetTime](/engine/Classes/classrpg_1_1os_1_1_o_s/#function-gettime)**()<br>Returns the time since initialization from glfw.  |
| void | **[SetMousePosition](/engine/Classes/classrpg_1_1os_1_1_o_s/#function-setmouseposition)**(double x, double y)<br>Sets the mouse cursor position relative to the upper-left corner of the window.  |
| void | **[GetMousePosition](/engine/Classes/classrpg_1_1os_1_1_o_s/#function-getmouseposition)**(double * x, double * y)<br>Gets the mouse cursor position relative to the upper-left corner of the window.  |
| bool | **[IsMouseLocked](/engine/Classes/classrpg_1_1os_1_1_o_s/#function-ismouselocked)**() |

## Public Attributes

|                | Name           |
| -------------- | -------------- |
| GLFWwindow * | **[focused_window](/engine/Classes/classrpg_1_1os_1_1_o_s/#variable-focused-window)**  |

## Additional inherited members

**Public Functions inherited from [rpg::events::EventQueue< KeyboardEvent >](/engine/Classes/classrpg_1_1events_1_1_event_queue/)**

|                | Name           |
| -------------- | -------------- |
| | **[EventQueue](/engine/Classes/classrpg_1_1events_1_1_event_queue/#function-eventqueue)**() |
| | **[EventQueue](/engine/Classes/classrpg_1_1events_1_1_event_queue/#function-eventqueue)**(eid entity_id) |
| virtual | **[~EventQueue](/engine/Classes/classrpg_1_1events_1_1_event_queue/#function-~eventqueue)**() =default |
| | **[EventQueue](/engine/Classes/classrpg_1_1events_1_1_event_queue/#function-eventqueue)**(const [EventQueue](/engine/Classes/classrpg_1_1events_1_1_event_queue/) & ) =default |
| [EventQueue](/engine/Classes/classrpg_1_1events_1_1_event_queue/) & | **[operator=](/engine/Classes/classrpg_1_1events_1_1_event_queue/#function-operator=)**(const [EventQueue](/engine/Classes/classrpg_1_1events_1_1_event_queue/) & ) =default |
| | **[EventQueue](/engine/Classes/classrpg_1_1events_1_1_event_queue/#function-eventqueue)**([EventQueue](/engine/Classes/classrpg_1_1events_1_1_event_queue/) && other) |
| [EventQueue](/engine/Classes/classrpg_1_1events_1_1_event_queue/) & | **[operator=](/engine/Classes/classrpg_1_1events_1_1_event_queue/#function-operator=)**([EventQueue](/engine/Classes/classrpg_1_1events_1_1_event_queue/) && other) |
| void | **[ProcessEventQueue](/engine/Classes/classrpg_1_1events_1_1_event_queue/#function-processeventqueue)**() |
| void | **[QueueEvent](/engine/Classes/classrpg_1_1events_1_1_event_queue/#function-queueevent)**([Event](/engine/Classes/structrpg_1_1events_1_1_event/)< T > && e) |

**Protected Attributes inherited from [rpg::events::EventQueue< KeyboardEvent >](/engine/Classes/classrpg_1_1events_1_1_event_queue/)**

|                | Name           |
| -------------- | -------------- |
| LockingQueue< [Event](/engine/Classes/structrpg_1_1events_1_1_event/)< T > > * | **[read_queue](/engine/Classes/classrpg_1_1events_1_1_event_queue/#variable-read-queue)**  |
| std::atomic< LockingQueue< [Event](/engine/Classes/structrpg_1_1events_1_1_event/)< T > > * > | **[write_queue](/engine/Classes/classrpg_1_1events_1_1_event_queue/#variable-write-queue)**  |

**Public Functions inherited from [rpg::events::EventQueue< MouseMoveEvent >](/engine/Classes/classrpg_1_1events_1_1_event_queue/)**

|                | Name           |
| -------------- | -------------- |
| | **[EventQueue](/engine/Classes/classrpg_1_1events_1_1_event_queue/#function-eventqueue)**() |
| | **[EventQueue](/engine/Classes/classrpg_1_1events_1_1_event_queue/#function-eventqueue)**(eid entity_id) |
| virtual | **[~EventQueue](/engine/Classes/classrpg_1_1events_1_1_event_queue/#function-~eventqueue)**() =default |
| | **[EventQueue](/engine/Classes/classrpg_1_1events_1_1_event_queue/#function-eventqueue)**(const [EventQueue](/engine/Classes/classrpg_1_1events_1_1_event_queue/) & ) =default |
| [EventQueue](/engine/Classes/classrpg_1_1events_1_1_event_queue/) & | **[operator=](/engine/Classes/classrpg_1_1events_1_1_event_queue/#function-operator=)**(const [EventQueue](/engine/Classes/classrpg_1_1events_1_1_event_queue/) & ) =default |
| | **[EventQueue](/engine/Classes/classrpg_1_1events_1_1_event_queue/#function-eventqueue)**([EventQueue](/engine/Classes/classrpg_1_1events_1_1_event_queue/) && other) |
| [EventQueue](/engine/Classes/classrpg_1_1events_1_1_event_queue/) & | **[operator=](/engine/Classes/classrpg_1_1events_1_1_event_queue/#function-operator=)**([EventQueue](/engine/Classes/classrpg_1_1events_1_1_event_queue/) && other) |
| void | **[ProcessEventQueue](/engine/Classes/classrpg_1_1events_1_1_event_queue/#function-processeventqueue)**() |
| void | **[QueueEvent](/engine/Classes/classrpg_1_1events_1_1_event_queue/#function-queueevent)**([Event](/engine/Classes/structrpg_1_1events_1_1_event/)< T > && e) |

**Protected Attributes inherited from [rpg::events::EventQueue< MouseMoveEvent >](/engine/Classes/classrpg_1_1events_1_1_event_queue/)**

|                | Name           |
| -------------- | -------------- |
| LockingQueue< [Event](/engine/Classes/structrpg_1_1events_1_1_event/)< T > > * | **[read_queue](/engine/Classes/classrpg_1_1events_1_1_event_queue/#variable-read-queue)**  |
| std::atomic< LockingQueue< [Event](/engine/Classes/structrpg_1_1events_1_1_event/)< T > > * > | **[write_queue](/engine/Classes/classrpg_1_1events_1_1_event_queue/#variable-write-queue)**  |

**Public Functions inherited from [rpg::events::EventQueue< MouseLockEvent >](/engine/Classes/classrpg_1_1events_1_1_event_queue/)**

|                | Name           |
| -------------- | -------------- |
| | **[EventQueue](/engine/Classes/classrpg_1_1events_1_1_event_queue/#function-eventqueue)**() |
| | **[EventQueue](/engine/Classes/classrpg_1_1events_1_1_event_queue/#function-eventqueue)**(eid entity_id) |
| virtual | **[~EventQueue](/engine/Classes/classrpg_1_1events_1_1_event_queue/#function-~eventqueue)**() =default |
| | **[EventQueue](/engine/Classes/classrpg_1_1events_1_1_event_queue/#function-eventqueue)**(const [EventQueue](/engine/Classes/classrpg_1_1events_1_1_event_queue/) & ) =default |
| [EventQueue](/engine/Classes/classrpg_1_1events_1_1_event_queue/) & | **[operator=](/engine/Classes/classrpg_1_1events_1_1_event_queue/#function-operator=)**(const [EventQueue](/engine/Classes/classrpg_1_1events_1_1_event_queue/) & ) =default |
| | **[EventQueue](/engine/Classes/classrpg_1_1events_1_1_event_queue/#function-eventqueue)**([EventQueue](/engine/Classes/classrpg_1_1events_1_1_event_queue/) && other) |
| [EventQueue](/engine/Classes/classrpg_1_1events_1_1_event_queue/) & | **[operator=](/engine/Classes/classrpg_1_1events_1_1_event_queue/#function-operator=)**([EventQueue](/engine/Classes/classrpg_1_1events_1_1_event_queue/) && other) |
| void | **[ProcessEventQueue](/engine/Classes/classrpg_1_1events_1_1_event_queue/#function-processeventqueue)**() |
| void | **[QueueEvent](/engine/Classes/classrpg_1_1events_1_1_event_queue/#function-queueevent)**([Event](/engine/Classes/structrpg_1_1events_1_1_event/)< T > && e) |

**Protected Attributes inherited from [rpg::events::EventQueue< MouseLockEvent >](/engine/Classes/classrpg_1_1events_1_1_event_queue/)**

|                | Name           |
| -------------- | -------------- |
| LockingQueue< [Event](/engine/Classes/structrpg_1_1events_1_1_event/)< T > > * | **[read_queue](/engine/Classes/classrpg_1_1events_1_1_event_queue/#variable-read-queue)**  |
| std::atomic< LockingQueue< [Event](/engine/Classes/structrpg_1_1events_1_1_event/)< T > > * > | **[write_queue](/engine/Classes/classrpg_1_1events_1_1_event_queue/#variable-write-queue)**  |

**Public Functions inherited from [rpg::events::EventQueue< WindowResizedEvent >](/engine/Classes/classrpg_1_1events_1_1_event_queue/)**

|                | Name           |
| -------------- | -------------- |
| | **[EventQueue](/engine/Classes/classrpg_1_1events_1_1_event_queue/#function-eventqueue)**() |
| | **[EventQueue](/engine/Classes/classrpg_1_1events_1_1_event_queue/#function-eventqueue)**(eid entity_id) |
| virtual | **[~EventQueue](/engine/Classes/classrpg_1_1events_1_1_event_queue/#function-~eventqueue)**() =default |
| | **[EventQueue](/engine/Classes/classrpg_1_1events_1_1_event_queue/#function-eventqueue)**(const [EventQueue](/engine/Classes/classrpg_1_1events_1_1_event_queue/) & ) =default |
| [EventQueue](/engine/Classes/classrpg_1_1events_1_1_event_queue/) & | **[operator=](/engine/Classes/classrpg_1_1events_1_1_event_queue/#function-operator=)**(const [EventQueue](/engine/Classes/classrpg_1_1events_1_1_event_queue/) & ) =default |
| | **[EventQueue](/engine/Classes/classrpg_1_1events_1_1_event_queue/#function-eventqueue)**([EventQueue](/engine/Classes/classrpg_1_1events_1_1_event_queue/) && other) |
| [EventQueue](/engine/Classes/classrpg_1_1events_1_1_event_queue/) & | **[operator=](/engine/Classes/classrpg_1_1events_1_1_event_queue/#function-operator=)**([EventQueue](/engine/Classes/classrpg_1_1events_1_1_event_queue/) && other) |
| void | **[ProcessEventQueue](/engine/Classes/classrpg_1_1events_1_1_event_queue/#function-processeventqueue)**() |
| void | **[QueueEvent](/engine/Classes/classrpg_1_1events_1_1_event_queue/#function-queueevent)**([Event](/engine/Classes/structrpg_1_1events_1_1_event/)< T > && e) |

**Protected Attributes inherited from [rpg::events::EventQueue< WindowResizedEvent >](/engine/Classes/classrpg_1_1events_1_1_event_queue/)**

|                | Name           |
| -------------- | -------------- |
| LockingQueue< [Event](/engine/Classes/structrpg_1_1events_1_1_event/)< T > > * | **[read_queue](/engine/Classes/classrpg_1_1events_1_1_event_queue/#variable-read-queue)**  |
| std::atomic< LockingQueue< [Event](/engine/Classes/structrpg_1_1events_1_1_event/)< T > > * > | **[write_queue](/engine/Classes/classrpg_1_1events_1_1_event_queue/#variable-write-queue)**  |

**Public Functions inherited from [rpg::util::NoMoveNoCopy](/engine/Classes/classrpg_1_1util_1_1_no_move_no_copy/)**

|                | Name           |
| -------------- | -------------- |
| | **[NoMoveNoCopy](/engine/Classes/classrpg_1_1util_1_1_no_move_no_copy/#function-nomovenocopy)**() =default |
| | **[~NoMoveNoCopy](/engine/Classes/classrpg_1_1util_1_1_no_move_no_copy/#function-~nomovenocopy)**() =default |
| | **[NoMoveNoCopy](/engine/Classes/classrpg_1_1util_1_1_no_move_no_copy/#function-nomovenocopy)**(const [NoMoveNoCopy](/engine/Classes/classrpg_1_1util_1_1_no_move_no_copy/) & ) =delete |
| void | **[operator=](/engine/Classes/classrpg_1_1util_1_1_no_move_no_copy/#function-operator=)**(const [NoMoveNoCopy](/engine/Classes/classrpg_1_1util_1_1_no_move_no_copy/) & ) =delete |
| | **[NoMoveNoCopy](/engine/Classes/classrpg_1_1util_1_1_no_move_no_copy/#function-nomovenocopy)**([NoMoveNoCopy](/engine/Classes/classrpg_1_1util_1_1_no_move_no_copy/) && ) =delete |
| void | **[operator=](/engine/Classes/classrpg_1_1util_1_1_no_move_no_copy/#function-operator=)**([NoMoveNoCopy](/engine/Classes/classrpg_1_1util_1_1_no_move_no_copy/) && ) =delete |


## Public Functions Documentation

### function InitializeWindow

```cpp
bool InitializeWindow(
    int width,
    int height,
    const std::string & title,
    config::GL_VERSION_PAIR requested_gl_version =config::PREFERRED_GL_VERSION,
    bool start_fullscreen =false
)
```

Initialize the rendering window and makes the window's context the current one. 

**Parameters**: 

  * **width** The window's client width 
  * **height** The window's client height 
  * **title** The title to show in the title bar and task manager. 
  * **requested_gl_version** OpenGL major version number. Must be >= OpenGL 3.3 
  * **start_fullscreen** Whether the window should be started in fullscreen mode. 


**Return**: If creation was successful or not. 

### function MakeCurrent

```cpp
void MakeCurrent() const
```

Make the context of the window current for the calling thread. 

### function SetWindowAspectRatio

```cpp
void SetWindowAspectRatio(
    int numerator =16,
    int denominator =9
) const
```

Sets the desired window aspect ratio numerator:denominator e.g. 16:9, 4:3. 

### function ToggleFullScreen

```cpp
void ToggleFullScreen() const
```

Toggles between fullscreen and windowed mode based. 

### function Quit

```cpp
void Quit() const
```

Tells the [OS](/engine/Classes/classrpg_1_1os_1_1_o_s/) that the active window should close. 

Since the main loop is based on that close status of that active window this effectively causes [Closing()](/engine/Classes/classrpg_1_1os_1_1_o_s/#function-closing) to return true during an upcoming message loop. 


### function Closing

```cpp
bool Closing() const
```

Checks if the window is closing. 

**Return**: True if the window is closing. 

### function SwapBuffers

```cpp
void SwapBuffers() const
```

Swap the front and back buffers. Call after rendering. If V-SYNC is on, this will block for swap interval. 

### function GetMonitorRefreshRate

```cpp
int GetMonitorRefreshRate() const
```

Returns the refresh rate that active window is on. 

**Return**: The monitor's refresh rate. 

### function OSMessageLoop

```cpp
void OSMessageLoop()
```

Processes events in the [OS](/engine/Classes/classrpg_1_1os_1_1_o_s/) message event loop. 

### function GetWindowWidth

```cpp
int GetWindowWidth() const
```

Gets the cached window width. 

**Return**: The window width. 

### function GetWindowHeight

```cpp
int GetWindowHeight() const
```

Gets the cached window height. 

**Return**: The window height. 

### function GetDeltaTime

```cpp
double GetDeltaTime()
```

Returns the time since the last call. 

**Return**: The amount of time that have passed since the last call in seconds. 

### function GetWindow

```cpp
GLFWwindow * GetWindow() const
```

Returns the current active window. 

**Return**: The current active window. 

### function DetachContext

```cpp
static void DetachContext()
```

Detach the context of the window from the calling thread. 

### function Terminate

```cpp
static void Terminate()
```

Calls GLFWTerminate to close the window. 

This is a static method so it can be called from anywhere to terminate the current window. 


### function GetTime

```cpp
static double GetTime()
```

Returns the time since initialization from glfw. 

**Return**: The amount of time since glfw was initialized in seconds. 

### function SetMousePosition

```cpp
static void SetMousePosition(
    double x,
    double y
)
```

Sets the mouse cursor position relative to the upper-left corner of the window. 

**Parameters**: 

  * **x** The new x coordinate of the mouse in screen coordinates. 
  * **y** The new y coordinate of the mouse in screen coordinates. 


### function GetMousePosition

```cpp
static void GetMousePosition(
    double * x,
    double * y
)
```

Gets the mouse cursor position relative to the upper-left corner of the window. 

**Parameters**: 

  * **x** The current x coordinate of the mouse in screen coordinates. 
  * **y** The current y coordinate of the mouse in screen coordinates. 


### function IsMouseLocked

```cpp
static inline bool IsMouseLocked()
```


## Public Attributes Documentation

### variable focused_window

```cpp
static GLFWwindow * focused_window {nullptr};
```


-------------------------------

Updated on 2022-07-10 at 17:53:08 -0500