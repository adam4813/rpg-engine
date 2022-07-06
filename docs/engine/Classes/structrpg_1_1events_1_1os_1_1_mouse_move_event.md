---
title: rpg::events::os::MouseMoveEvent

---

# rpg::events::os::MouseMoveEvent



 [More...](#detailed-description)


`#include <os-events.hpp>`

## Public Attributes

|                | Name           |
| -------------- | -------------- |
| double | **[norm_x](/engine/Classes/structrpg_1_1events_1_1os_1_1_mouse_move_event/#variable-norm-x)**  |
| double | **[norm_y](/engine/Classes/structrpg_1_1events_1_1os_1_1_mouse_move_event/#variable-norm-y)**  |
| int | **[old_x](/engine/Classes/structrpg_1_1events_1_1os_1_1_mouse_move_event/#variable-old-x)** <br>Resolution independent new x, y (0-1) from upper-left to lower-right.  |
| int | **[old_y](/engine/Classes/structrpg_1_1events_1_1os_1_1_mouse_move_event/#variable-old-y)**  |
| int | **[new_x](/engine/Classes/structrpg_1_1events_1_1os_1_1_mouse_move_event/#variable-new-x)** <br>[Client](/engine/Classes/classrpg_1_1_client/) space old x, y.  |
| int | **[new_y](/engine/Classes/structrpg_1_1events_1_1os_1_1_mouse_move_event/#variable-new-y)**  |

## Detailed Description

```cpp
struct rpg::events::os::MouseMoveEvent;
```


Mouse change of position event 

## Public Attributes Documentation

### variable norm_x

```cpp
double norm_x {0.0};
```


### variable norm_y

```cpp
double norm_y {0.0};
```


### variable old_x

```cpp
int old_x {0};
```

Resolution independent new x, y (0-1) from upper-left to lower-right. 

### variable old_y

```cpp
int old_y {0};
```


### variable new_x

```cpp
int new_x {0};
```

[Client](/engine/Classes/classrpg_1_1_client/) space old x, y. 

### variable new_y

```cpp
int new_y {0};
```


-------------------------------

Updated on 2022-07-06 at 03:45:29 +0000