#include "game.hpp"

#include <iostream>
#include <sstream>

namespace rpg {
void Game::Init() const {
	for (const auto& worker : this->update_threads) {
		worker->StartThread();
	}
}

void Game::Update(const double delta) const {
	for (const auto& worker : this->update_threads) {
		worker->SetDelta(delta);
	}
	for (const auto& worker : this->update_threads) {
		worker->AwaitCompletion();
	}
}

void Game::AddUpdateThread(std::unique_ptr<UpdateThread> thread) { this->update_threads.emplace(std::move(thread)); }
} // namespace rpg
