---
title: rpg::events::EventQueue

---

# rpg::events::EventQueue



 [More...](#detailed-description)

Inherited by [rpg::os::OS](/engine/Classes/classrpg_1_1os_1_1_o_s/), [rpg::os::OS](/engine/Classes/classrpg_1_1os_1_1_o_s/), [rpg::os::OS](/engine/Classes/classrpg_1_1os_1_1_o_s/), [rpg::os::OS](/engine/Classes/classrpg_1_1os_1_1_o_s/)

## Public Functions

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
| virtual void | **[On](/engine/Classes/classrpg_1_1events_1_1_event_queue/#function-on)**(const eid, std::shared_ptr< T > ) |
| virtual void | **[On](/engine/Classes/classrpg_1_1events_1_1_event_queue/#function-on)**(std::shared_ptr< T > ) |

## Protected Attributes

|                | Name           |
| -------------- | -------------- |
| LockingQueue< [Event](/engine/Classes/structrpg_1_1events_1_1_event/)< T > > * | **[read_queue](/engine/Classes/classrpg_1_1events_1_1_event_queue/#variable-read-queue)**  |
| std::atomic< LockingQueue< [Event](/engine/Classes/structrpg_1_1events_1_1_event/)< T > > * > | **[write_queue](/engine/Classes/classrpg_1_1events_1_1_event_queue/#variable-write-queue)**  |

## Detailed Description

```cpp
template <class T >
class rpg::events::EventQueue;
```

## Public Functions Documentation

### function EventQueue

```cpp
inline EventQueue()
```


### function EventQueue

```cpp
inline explicit EventQueue(
    eid entity_id
)
```


### function ~EventQueue

```cpp
virtual ~EventQueue() =default
```


### function EventQueue

```cpp
EventQueue(
    const EventQueue & 
) =default
```


### function operator=

```cpp
EventQueue & operator=(
    const EventQueue & 
) =default
```


### function EventQueue

```cpp
inline EventQueue(
    EventQueue && other
)
```


### function operator=

```cpp
inline EventQueue & operator=(
    EventQueue && other
)
```


### function ProcessEventQueue

```cpp
inline void ProcessEventQueue()
```


### function QueueEvent

```cpp
inline void QueueEvent(
    Event< T > && e
)
```


### function On

```cpp
inline virtual void On(
    const eid,
    std::shared_ptr< T > 
)
```


### function On

```cpp
inline virtual void On(
    std::shared_ptr< T > 
)
```


## Protected Attributes Documentation

### variable read_queue

```cpp
LockingQueue< Event< T > > * read_queue;
```


### variable write_queue

```cpp
std::atomic< LockingQueue< Event< T > > * > write_queue;
```


-------------------------------

Updated on 2022-07-06 at 03:45:29 +0000