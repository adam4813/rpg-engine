#pragma once

#include "util/types.hpp"
#include <memory>

namespace rpg::events {
// Container to hold event data. This is stored in the queue rather than raw event data.
template <class T> struct Event {
	Event(const eid entity_id, std::shared_ptr<T> data) : entity_id(entity_id), data(std::move(data)) {}
	explicit Event(std::shared_ptr<T> data) : Event(0, data) {}
	~Event() = default;
	Event(Event&) = delete;
	Event(Event&& other) noexcept : entity_id(other.entity_id), data(std::move(other.data)) {}
	Event& operator=(const Event&) = delete;
	Event& operator=(Event&& right) noexcept {
		this->entity_id = right.entity_id;
		this->data = std::move(right.data);
		return *this;
	}

	eid entity_id;
	std::shared_ptr<T> data;
};
} // namespace rpg::events
