#pragma once

#include <functional>
#include <future>
#include <optional>
#include <thread>

namespace rpg::util {
typedef void(updateable)(double);

class UpdateThread {
public:
	struct Methods {
		std::function<updateable> update;
		std::optional<std::function<void()>> spawn{};
		std::optional<std::function<void()>> despawn{};
	};

	explicit UpdateThread(Methods methods) : methods(std::move(methods)) {}

	void StartThread() { this->thread = std::jthread(std::bind_front(&UpdateThread::UpdateLoop, this)); }

	void UpdateLoop(const std::stop_token& stop_token) {
		if (this->methods.spawn.has_value()) {
			this->methods.spawn.value()();
		}
		std::future<double> delta_future = this->delta_promise.get_future();
		while (!stop_token.stop_requested()) {
			if (!delta_future.valid()) {
				continue;
			}
			using namespace std::chrono_literals;
			// 500ms limit status check. In case other threads have become stuck.
			if (const auto status = delta_future.wait_for(500ms); status != std::future_status::ready) {
				continue;
			}

			this->methods.update(delta_future.get());

			this->delta_promise = std::promise<double>();
			delta_future = delta_promise.get_future();
			completion_promise.set_value();

			std::this_thread::yield();
		}
		if (this->methods.despawn.has_value()) {
			this->methods.despawn.value()();
		}
	}

	void SetDelta(const double delta) { this->delta_promise.set_value(delta); }

	void AwaitCompletion() {
		this->completion_promise.get_future().wait();
		this->completion_promise = std::promise<void>();
	}

private:
	std::promise<double> delta_promise;
	std::promise<void> completion_promise;
	std::jthread thread;
	Methods methods;
};
} // namespace rpg::util
