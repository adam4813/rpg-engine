#pragma once

#include <atomic>
#include <memory>
#include <mutex>
#include <queue>

#include "event-dispatcher.hpp"
#include "event.hpp"

namespace rpg::events {
// Thread friendly double queue for incoming events. Call EventQueue<T>::ProcessEventQueue()
// to iterate over all queued events when it is safe to modify state. You must
// qualify the call with the base class and template type to avoid ambiguity.
template <class T> class EventQueue {
	// Helper class containing a std::queue. The std::queue is NOT thread safe
	// so we can end up with an "Emplace" in-flight while the queue is being read
	// this can lead to a race condition where the item is pop()'ed before Emplace finishes
	// that is all kinds of bad, so this wraps it with a simple spinlock if a write was happening
	template <class U> struct LockingQueue {
		void Emplace(U&& e) {
			std::scoped_lock lock(queue_write);
			queue.emplace(std::move(e));
		}
		std::queue<U> queue;
		std::mutex queue_write;
	};

public:
	EventQueue() : read_queue(new LockingQueue<Event<T>>()), write_queue(new LockingQueue<Event<T>>()) {
		EventDispatcher<T>::Subscribe(this);
	}
	// Causes subscribing to events for only a specific entity_id.
	explicit EventQueue(eid entity_id) :
			read_queue(new std::queue<Event<T>>()), write_queue(new std::queue<Event<T>>()) {
		EventDispatcher<T>::Subscribe(entity_id, this);
	}
	virtual ~EventQueue() = default;
	EventQueue(const EventQueue&) = default;
	EventQueue& operator=(const EventQueue&) = default;
	EventQueue(EventQueue&& other) noexcept {
		this->read_queue = std::move(other.read_queue);
		this->write_queue = std::move(other.write_queue);
	}
	EventQueue& operator=(EventQueue&& other) noexcept {
		this->read_queue = std::move(other.read_queue);
		this->write_queue = std::move(other.write_queue);
		return *this;
	}

	void ProcessEventQueue() {
		auto typed_queue = static_cast<EventQueue<T>*>(this);
		this->read_queue = write_queue.exchange(this->read_queue);
		std::scoped_lock lock(this->read_queue->queue_write);
		while (!this->read_queue->queue.empty()) {
			if (Event e{std::move(this->read_queue->queue.front())}; e.entity_id == 0) {
				typed_queue->On(e.data);
			}
			else {
				typed_queue->On(e.entity_id, e.data);
			}
			this->read_queue->queue.pop();
		}
	}

	void QueueEvent(Event<T>&& e) { (*write_queue).Emplace(std::move(e)); }

	virtual void On(const eid, std::shared_ptr<T>) {}
	virtual void On(std::shared_ptr<T>) {}

protected:
	LockingQueue<Event<T>>* read_queue;
	std::atomic<LockingQueue<Event<T>>*> write_queue;
};

} // namespace rpg::events
