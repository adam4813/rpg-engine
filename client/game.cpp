#include "game.hpp"

namespace rpg {
void Game::Init() {
	for (UpdateThread& worker : this->update_threads) {
		worker.StartThread();
	}
}

void Game::Update(const double delta) {
	for (UpdateThread& worker : this->update_threads) {
		worker.SetDelta(delta);
	}
	for (UpdateThread& worker : this->update_threads) {
		worker.AwaitCompletion();
	}
}

void Game::AddUpdateThread(UpdateThread thread) { this->update_threads.emplace_back(std::move(thread)); }
} // namespace rpg
