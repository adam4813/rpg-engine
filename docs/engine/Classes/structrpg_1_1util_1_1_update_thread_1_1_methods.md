---
title: rpg::util::UpdateThread::Methods

---

# rpg::util::UpdateThread::Methods





## Public Attributes

|                | Name           |
| -------------- | -------------- |
| std::function< updateable > | **[update](/engine/Classes/structrpg_1_1util_1_1_update_thread_1_1_methods/#variable-update)**  |
| std::optional< std::function< void()> > | **[spawn](/engine/Classes/structrpg_1_1util_1_1_update_thread_1_1_methods/#variable-spawn)**  |
| std::optional< std::function< void()> > | **[despawn](/engine/Classes/structrpg_1_1util_1_1_update_thread_1_1_methods/#variable-despawn)**  |

## Public Attributes Documentation

### variable update

```cpp
std::function< updateable > update;
```


### variable spawn

```cpp
std::optional< std::function< void()> > spawn {};
```


### variable despawn

```cpp
std::optional< std::function< void()> > despawn {};
```


-------------------------------

Updated on 2022-07-06 at 03:45:30 +0000