---
title: rpg::os::OSEventHandler

---

# rpg::os::OSEventHandler





## Public Functions

|                | Name           |
| -------------- | -------------- |
| void | **[RegisterHandlers](/engine/Classes/classrpg_1_1os_1_1_o_s_event_handler/#function-registerhandlers)**(GLFWwindow * target_window) |
| void | **[DispatchKeyboardEvent](/engine/Classes/classrpg_1_1os_1_1_o_s_event_handler/#function-dispatchkeyboardevent)**(int key, int scancode, int action, int mods) const<br>Dispatches keyboard events from the callback.  |
| void | **[DispatchCharacterEvent](/engine/Classes/classrpg_1_1os_1_1_o_s_event_handler/#function-dispatchcharacterevent)**(unsigned int unicode_char) const<br>Dispatches a character event.  |
| void | **[DispatchMouseMoveEvent](/engine/Classes/classrpg_1_1os_1_1_o_s_event_handler/#function-dispatchmousemoveevent)**(double x, double y)<br>Dispatches mouse movement events.  |
| void | **[DispatchMouseScrollEvent](/engine/Classes/classrpg_1_1os_1_1_o_s_event_handler/#function-dispatchmousescrollevent)**(double x_offset, double y_offset) const<br>Dispatches mouse scroll events.  |
| void | **[DispatchMouseButtonEvent](/engine/Classes/classrpg_1_1os_1_1_o_s_event_handler/#function-dispatchmousebuttonevent)**(int button, int action, int mods) const<br>Dispatches mouse button events from the callback.  |
| void | **[DispatchFileDropEvent](/engine/Classes/classrpg_1_1os_1_1_o_s_event_handler/#function-dispatchfiledropevent)**(int count, const char ** paths) const<br>Dispatches a character event.  |
| void | **[DispatchWindowResizedEvent](/engine/Classes/classrpg_1_1os_1_1_o_s_event_handler/#function-dispatchwindowresizedevent)**(int width, int height)<br>Dispatches a window resized event.  |

## Public Functions Documentation

### function RegisterHandlers

```cpp
void RegisterHandlers(
    GLFWwindow * target_window
)
```


### function DispatchKeyboardEvent

```cpp
void DispatchKeyboardEvent(
    int key,
    int scancode,
    int action,
    int mods
) const
```

Dispatches keyboard events from the callback. 

**Parameters**: 

  * **key** ASCII key number. 
  * **scancode** The converted key value 
  * **action** The event type. 
  * **mods** Modifier keys. 


### function DispatchCharacterEvent

```cpp
void DispatchCharacterEvent(
    unsigned int unicode_char
) const
```

Dispatches a character event. 

**Parameters**: 

  * **unicode_char** The Unicode character key code. 


### function DispatchMouseMoveEvent

```cpp
void DispatchMouseMoveEvent(
    double x,
    double y
)
```

Dispatches mouse movement events. 

**Parameters**: 

  * **x** The new x coordinate of the mouse in screen coordinates. 
  * **y** The new y coordinate of the mouse in screen coordinates. 


It determines the changes in mouse position and stores the new position for later. 


### function DispatchMouseScrollEvent

```cpp
void DispatchMouseScrollEvent(
    double x_offset,
    double y_offset
) const
```

Dispatches mouse scroll events. 

**Parameters**: 

  * **x_offset** The delta x coordinate of the mouse wheel 
  * **y_offset** The delta y coordinate of the mouse wheel. 


It determines the changes in mouse position and stores the new position for later. 


### function DispatchMouseButtonEvent

```cpp
void DispatchMouseButtonEvent(
    int button,
    int action,
    int mods
) const
```

Dispatches mouse button events from the callback. 

**Parameters**: 

  * **button** The button that the action occurred on. 
  * **action** The action that occurred. 
  * **mods** Modifier keys. 


### function DispatchFileDropEvent

```cpp
void DispatchFileDropEvent(
    int count,
    const char ** paths
) const
```

Dispatches a character event. 

**Parameters**: 

  * **count** The number of files dropped. 
  * **paths** Array of filenames. 


### function DispatchWindowResizedEvent

```cpp
void DispatchWindowResizedEvent(
    int width,
    int height
)
```

Dispatches a window resized event. 

**Parameters**: 

  * **width** The client window width. 
  * **height** The client window height. 


-------------------------------

Updated on 2022-07-10 at 17:53:08 -0500