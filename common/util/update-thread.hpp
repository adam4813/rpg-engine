#pragma once

#include "nomovenocopy.hpp"

#include <functional>
#include <future>
#include <optional>
#include <thread>

namespace rpg::util {
typedef void(updateable)(double);

class UpdateThread : public NoMoveNoCopy {
public:
	static std::unique_ptr<UpdateThread>
	Create(const std::function<updateable>& update_function,
		   const std::optional<std::function<void()>>& spawn_function = {}) {
		auto update_thread = std::make_unique<UpdateThread>();
		update_thread->update_function = update_function;
		update_thread->spawn_function = spawn_function;
		return update_thread;
	}

	void StartThread() { this->thread = std::jthread(std::bind_front(&UpdateThread::UpdateLoop, this)); }

	void UpdateLoop(const std::stop_token& stop_token) {
		if (spawn_function.has_value()) {
			spawn_function.value()();
		}
		std::future<double> delta_future = this->delta_promise.get_future();
		while (!stop_token.stop_requested()) {
			// 500ms limit status check. In case other threads have become stuck.
			if (const auto status = delta_future.wait_for(std::chrono::milliseconds(500));
				status != std::future_status::ready) {
				continue;
			}

			update_function(delta_future.get());

			this->delta_promise = std::promise<double>();
			delta_future = delta_promise.get_future();
			completion_promise.set_value();
			
			std::this_thread::yield();
		}
	}

	void SetDelta(const double delta) { this->delta_promise.set_value(delta); }

	void AwaitCompletion() {
		this->completion_promise.get_future().wait();
		this->completion_promise = std::promise<void>();
	}

private:
	std::function<updateable> update_function;
	std::optional<std::function<void()>> spawn_function;
	std::promise<double> delta_promise;
	std::promise<void> completion_promise;
	std::jthread thread;
	std::mutex m;
	std::condition_variable cv;
};
} // namespace rpg::util
