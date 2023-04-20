---
title: rpg::util::UpdateThread

---

# rpg::util::UpdateThread





## Public Classes

|                | Name           |
| -------------- | -------------- |
| struct | **[Methods](/engine/Classes/structrpg_1_1util_1_1_update_thread_1_1_methods/)**  |

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[UpdateThread](/engine/Classes/classrpg_1_1util_1_1_update_thread/#function-updatethread)**([Methods](/engine/Classes/structrpg_1_1util_1_1_update_thread_1_1_methods/) methods) |
| void | **[StartThread](/engine/Classes/classrpg_1_1util_1_1_update_thread/#function-startthread)**() |
| void | **[UpdateLoop](/engine/Classes/classrpg_1_1util_1_1_update_thread/#function-updateloop)**(const std::stop_token & stop_token) |
| void | **[SetDelta](/engine/Classes/classrpg_1_1util_1_1_update_thread/#function-setdelta)**(const double delta) |
| void | **[AwaitCompletion](/engine/Classes/classrpg_1_1util_1_1_update_thread/#function-awaitcompletion)**() |

## Public Functions Documentation

### function UpdateThread

```cpp
inline explicit UpdateThread(
    Methods methods
)
```


### function StartThread

```cpp
inline void StartThread()
```


### function UpdateLoop

```cpp
inline void UpdateLoop(
    const std::stop_token & stop_token
)
```


### function SetDelta

```cpp
inline void SetDelta(
    const double delta
)
```


### function AwaitCompletion

```cpp
inline void AwaitCompletion()
```


-------------------------------

Updated on 2022-07-10 at 17:53:08 -0500