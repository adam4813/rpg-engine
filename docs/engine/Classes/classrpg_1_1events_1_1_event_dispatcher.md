---
title: rpg::events::EventDispatcher

---

# rpg::events::EventDispatcher



 [More...](#detailed-description)

Inherits from [rpg::util::NoMoveNoCopy](/engine/Classes/classrpg_1_1util_1_1_no_move_no_copy/)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| void | **[Subscribe](/engine/Classes/classrpg_1_1events_1_1_event_dispatcher/#function-subscribe)**(const eid entity_id, [EventQueue](/engine/Classes/classrpg_1_1events_1_1_event_queue/)< T > * subscriber)<br>Subscribes to be notified of events.  |
| void | **[Subscribe](/engine/Classes/classrpg_1_1events_1_1_event_dispatcher/#function-subscribe)**([EventQueue](/engine/Classes/classrpg_1_1events_1_1_event_queue/)< T > * subscriber)<br>Subscribes to be notified of events for all entity IDs.  |
| void | **[Unsubscribe](/engine/Classes/classrpg_1_1events_1_1_event_dispatcher/#function-unsubscribe)**(const eid entity_id, [EventQueue](/engine/Classes/classrpg_1_1events_1_1_event_queue/)< T > * subscriber)<br>Unsubscribe to notification of events.  |
| void | **[Unsubscribe](/engine/Classes/classrpg_1_1events_1_1_event_dispatcher/#function-unsubscribe)**([EventQueue](/engine/Classes/classrpg_1_1events_1_1_event_queue/)< T > * subscriber)<br>Unsubscribe to notification of events.  |
| void | **[Emit](/engine/Classes/classrpg_1_1events_1_1_event_dispatcher/#function-emit)**(const eid entity_id, std::shared_ptr< T > data)<br>Emits an event to subscribers for a given entity_id and to all subscribers listening for events for any entity_id.  |
| void | **[Emit](/engine/Classes/classrpg_1_1events_1_1_event_dispatcher/#function-emit)**(std::shared_ptr< T > data)<br>Emits an event to all subscribers listening for events for any entity_id.  |

## Additional inherited members

**Public Functions inherited from [rpg::util::NoMoveNoCopy](/engine/Classes/classrpg_1_1util_1_1_no_move_no_copy/)**

|                | Name           |
| -------------- | -------------- |
| | **[NoMoveNoCopy](/engine/Classes/classrpg_1_1util_1_1_no_move_no_copy/#function-nomovenocopy)**() =default |
| | **[~NoMoveNoCopy](/engine/Classes/classrpg_1_1util_1_1_no_move_no_copy/#function-~nomovenocopy)**() =default |
| | **[NoMoveNoCopy](/engine/Classes/classrpg_1_1util_1_1_no_move_no_copy/#function-nomovenocopy)**(const [NoMoveNoCopy](/engine/Classes/classrpg_1_1util_1_1_no_move_no_copy/) & ) =delete |
| void | **[operator=](/engine/Classes/classrpg_1_1util_1_1_no_move_no_copy/#function-operator=)**(const [NoMoveNoCopy](/engine/Classes/classrpg_1_1util_1_1_no_move_no_copy/) & ) =delete |
| | **[NoMoveNoCopy](/engine/Classes/classrpg_1_1util_1_1_no_move_no_copy/#function-nomovenocopy)**([NoMoveNoCopy](/engine/Classes/classrpg_1_1util_1_1_no_move_no_copy/) && ) =delete |
| void | **[operator=](/engine/Classes/classrpg_1_1util_1_1_no_move_no_copy/#function-operator=)**([NoMoveNoCopy](/engine/Classes/classrpg_1_1util_1_1_no_move_no_copy/) && ) =delete |


## Detailed Description

```cpp
template <typename T >
class rpg::events::EventDispatcher;
```

## Public Functions Documentation

### function Subscribe

```cpp
static inline void Subscribe(
    const eid entity_id,
    EventQueue< T > * subscriber
)
```

Subscribes to be notified of events. 

**Parameters**: 

  * **entity_id** ID of the entity to subscribe to. 
  * **subscriber** The subscriber to add. 


### function Subscribe

```cpp
static inline void Subscribe(
    EventQueue< T > * subscriber
)
```

Subscribes to be notified of events for all entity IDs. 

**Parameters**: 

  * **subscriber** The subscriber to add. 


### function Unsubscribe

```cpp
static inline void Unsubscribe(
    const eid entity_id,
    EventQueue< T > * subscriber
)
```

Unsubscribe to notification of events. 

**Parameters**: 

  * **entity_id** ID of the entity to unsubscribe from. 
  * **subscriber** The subscriber to remove. 


### function Unsubscribe

```cpp
static inline void Unsubscribe(
    EventQueue< T > * subscriber
)
```

Unsubscribe to notification of events. 

**Parameters**: 

  * **subscriber** The subscriber to remove. 


### function Emit

```cpp
static inline void Emit(
    const eid entity_id,
    std::shared_ptr< T > data
)
```

Emits an event to subscribers for a given entity_id and to all subscribers listening for events for any entity_id. 

**Parameters**: 

  * **entity_id** ID of the entity the event happen to. 
  * **data** The event data. 


### function Emit

```cpp
static inline void Emit(
    std::shared_ptr< T > data
)
```

Emits an event to all subscribers listening for events for any entity_id. 

**Parameters**: 

  * **data** The changed data. 


-------------------------------

Updated on 2022-07-10 at 17:53:08 -0500