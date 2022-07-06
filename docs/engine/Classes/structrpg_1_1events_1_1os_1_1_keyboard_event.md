---
title: rpg::events::os::KeyboardEvent

---

# rpg::events::os::KeyboardEvent





## Public Types

|                | Name           |
| -------------- | -------------- |
| enum class| **[KEY_ACTION](/engine/Classes/structrpg_1_1events_1_1os_1_1_keyboard_event/#enum-key-action)** { KEY_DOWN, KEY_UP, KEY_REPEAT, KEY_CHAR} |

## Public Attributes

|                | Name           |
| -------------- | -------------- |
| int | **[key](/engine/Classes/structrpg_1_1events_1_1os_1_1_keyboard_event/#variable-key)**  |
| int | **[scancode](/engine/Classes/structrpg_1_1events_1_1os_1_1_keyboard_event/#variable-scancode)**  |
| KEY_ACTION | **[action](/engine/Classes/structrpg_1_1events_1_1os_1_1_keyboard_event/#variable-action)**  |
| int | **[mods](/engine/Classes/structrpg_1_1events_1_1os_1_1_keyboard_event/#variable-mods)**  |

## Public Types Documentation

### enum KEY_ACTION

| Enumerator | Value | Description |
| ---------- | ----- | ----------- |
| KEY_DOWN | |   |
| KEY_UP | |   |
| KEY_REPEAT | |   |
| KEY_CHAR | |   |




## Public Attributes Documentation

### variable key

```cpp
int key {0};
```


### variable scancode

```cpp
int scancode {0};
```


### variable action

```cpp
KEY_ACTION action {KEY_ACTION::KEY_DOWN};
```


### variable mods

```cpp
int mods {0};
```


-------------------------------

Updated on 2022-07-06 at 03:45:29 +0000