#pragma once

#include "util/types.hpp"

#include <components.pb.h>

namespace rpg::events {

struct EntityCreated {
	proto::Entity entity;
};

struct EntityDestroyed {
	eid entity_id{0};
};

struct FocusCapturedEvent {
	eid entity_id;
	bool keyboard;
	bool mouse;
};
struct FocusBlurEvent {
	eid entity_id;
	bool keyboard;
	bool mouse;
};
} // namespace rpg::events
