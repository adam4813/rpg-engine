#pragma once

#include <vector>

#include <util/update-thread.hpp>

namespace rpg {
using util::UpdateThread;
class Game {
public:
	void Init();

	void Update(double delta);

	void AddUpdateThread(UpdateThread);

private:
	std::vector<UpdateThread> update_threads;
};
} // namespace rpg
