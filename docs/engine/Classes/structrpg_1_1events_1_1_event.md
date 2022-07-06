---
title: rpg::events::Event

---

# rpg::events::Event



 [More...](#detailed-description)

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[Event](/engine/Classes/structrpg_1_1events_1_1_event/#function-event)**(const eid entity_id, std::shared_ptr< T > data) |
| | **[Event](/engine/Classes/structrpg_1_1events_1_1_event/#function-event)**(std::shared_ptr< T > data) |
| | **[~Event](/engine/Classes/structrpg_1_1events_1_1_event/#function-~event)**() =default |
| | **[Event](/engine/Classes/structrpg_1_1events_1_1_event/#function-event)**([Event](/engine/Classes/structrpg_1_1events_1_1_event/) & ) =delete |
| | **[Event](/engine/Classes/structrpg_1_1events_1_1_event/#function-event)**([Event](/engine/Classes/structrpg_1_1events_1_1_event/) && other) |
| [Event](/engine/Classes/structrpg_1_1events_1_1_event/) & | **[operator=](/engine/Classes/structrpg_1_1events_1_1_event/#function-operator=)**(const [Event](/engine/Classes/structrpg_1_1events_1_1_event/) & ) =delete |
| [Event](/engine/Classes/structrpg_1_1events_1_1_event/) & | **[operator=](/engine/Classes/structrpg_1_1events_1_1_event/#function-operator=)**([Event](/engine/Classes/structrpg_1_1events_1_1_event/) && right) |

## Public Attributes

|                | Name           |
| -------------- | -------------- |
| eid | **[entity_id](/engine/Classes/structrpg_1_1events_1_1_event/#variable-entity-id)**  |
| std::shared_ptr< T > | **[data](/engine/Classes/structrpg_1_1events_1_1_event/#variable-data)**  |

## Detailed Description

```cpp
template <class T >
struct rpg::events::Event;
```

## Public Functions Documentation

### function Event

```cpp
inline Event(
    const eid entity_id,
    std::shared_ptr< T > data
)
```


### function Event

```cpp
inline explicit Event(
    std::shared_ptr< T > data
)
```


### function ~Event

```cpp
~Event() =default
```


### function Event

```cpp
Event(
    Event & 
) =delete
```


### function Event

```cpp
inline Event(
    Event && other
)
```


### function operator=

```cpp
Event & operator=(
    const Event & 
) =delete
```


### function operator=

```cpp
inline Event & operator=(
    Event && right
)
```


## Public Attributes Documentation

### variable entity_id

```cpp
eid entity_id;
```


### variable data

```cpp
std::shared_ptr< T > data;
```


-------------------------------

Updated on 2022-07-06 at 03:45:29 +0000