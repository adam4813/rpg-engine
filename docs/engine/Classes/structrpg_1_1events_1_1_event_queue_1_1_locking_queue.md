---
title: rpg::events::EventQueue::LockingQueue

---

# rpg::events::EventQueue::LockingQueue



 [More...](#detailed-description)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| void | **[Emplace](/engine/Classes/structrpg_1_1events_1_1_event_queue_1_1_locking_queue/#function-emplace)**(U && e) |

## Public Attributes

|                | Name           |
| -------------- | -------------- |
| std::queue< U > | **[queue](/engine/Classes/structrpg_1_1events_1_1_event_queue_1_1_locking_queue/#variable-queue)**  |
| std::mutex | **[queue_write](/engine/Classes/structrpg_1_1events_1_1_event_queue_1_1_locking_queue/#variable-queue-write)**  |

## Detailed Description

```cpp
template <class U >
struct rpg::events::EventQueue::LockingQueue;
```

## Public Functions Documentation

### function Emplace

```cpp
inline void Emplace(
    U && e
)
```


## Public Attributes Documentation

### variable queue

```cpp
std::queue< U > queue;
```


### variable queue_write

```cpp
std::mutex queue_write;
```


-------------------------------

Updated on 2022-07-06 at 03:45:29 +0000