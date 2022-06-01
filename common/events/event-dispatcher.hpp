#pragma once

#include <list>
#include <map>
#include <memory>

#include "event.hpp"
#include "util/nomovenocopy.hpp"

namespace rpg::events {

template <class T> class EventQueue;

template <typename T> class EventDispatcher final : public util::NoMoveNoCopy {
public:
	/**
	* @brief Subscribes to be notified of events
	*
	* @param entity_id ID of the entity to subscribe to.
	* @param subscriber The subscriber to add.
	*/
	static void Subscribe(const eid entity_id, EventQueue<T>* subscriber) {
		auto subs = subscribers.find(entity_id);
		if (subs == subscribers.end()) {
			// no subscriptions for entity, add the entity and subscriber
			subscribers[entity_id].push_back(subscriber);
		}
		else {
			if (std::find(subs->second.begin(), subs->second.end(), subscriber) == subs->second.end()) {
				subs->second.push_back(subscriber);
			}
		}
	}

	/**
	* @brief Subscribes to be notified of events for all entity IDs.
	*
	* @param subscriber The subscriber to add.
	*/
	static void Subscribe(EventQueue<T>* subscriber) { Subscribe(0, subscriber); }

	/**
	* @brief Unsubscribe to notification of events.
	*
	* @param entity_id ID of the entity to unsubscribe from.
	* @param subscriber The subscriber to remove.
	*/
	static void Unsubscribe(const eid entity_id, EventQueue<T>* subscriber) {
		if (subscribers.contains(entity_id)) {
			subscribers[entity_id].remove(subscriber);
		}
	}

	/**
	* @brief Unsubscribe to notification of events.
	*
	* @param subscriber The subscriber to remove.
	*/
	static void Unsubscribe(EventQueue<T>* subscriber) { Unsubscribe(0, subscriber); }

	/**
	* @brief Emits an event to subscribers for a given entity_id and to all
	* subscribers listening for events for any entity_id.
	*
	* @param entity_id ID of the entity the event happen to.
	* @param data The event data.
	*/
	static void Emit(const eid entity_id, std::shared_ptr<T> data) {
		if (subscribers.contains(entity_id)) {
			for (EventQueue<T>* subscriber : subscribers.at(entity_id)) {
				subscriber->QueueEvent(Event<T>{entity_id, data});
			}
		}
	}

	/**
	* @brief Emits an event to all subscribers listening for events for any entity_id.
	*
	* @param data The changed data.
	*/
	static void Emit(std::shared_ptr<T> data) { Emit(0, data); }

private:
	inline static std::map<eid, std::list<EventQueue<T>*>> subscribers{std::make_pair(0, std::list<EventQueue<T>*>())};
};
} // namespace rpg::events
