#pragma once

#include <memory>
#include <set>

#include <util/update-thread.hpp>

namespace rpg {
using util::UpdateThread;
class Game {
public:
	void Init() const;

	void Update(double delta) const;

	void AddUpdateThread(std::unique_ptr<UpdateThread>);

private:
	std::set<std::unique_ptr<UpdateThread>> update_threads;
};
} // namespace rpg
