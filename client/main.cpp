#include <iostream>
#include <test.hpp>

#include "constants.hpp"
#include "game.hpp"
#include "graphics/render-system.hpp"
#include "os/os.hpp"
#include <spdlog/sinks/stdout_sinks.h>

using namespace rpg::os;

auto InitializeLogger(const spdlog::level::level_enum log_level) {
	std::vector<spdlog::sink_ptr> sinks;
	sinks.push_back(std::make_shared<spdlog::sinks::stdout_sink_mt>());
	auto log = std::make_shared<spdlog::logger>("console_log", begin(sinks), end(sinks));
	log->set_level(log_level);
	log->set_pattern("%v"); // [%l] [thread %t] %v"); // Format on stdout
	spdlog::register_logger(log);
	return log;
}

int main(int argc, char const* argv[]) {
	const auto log = InitializeLogger(spdlog::level::debug);

	OS os;

	using namespace rpg::config;
	log->info("Initializing OpenGL...");
	if (!os.InitializeWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE)) {
		log->warn("The OpenGL 4.0 context wasn't created properly, attempting fallback");
		if (!os.InitializeWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, FALLBACK_GL_VERSION)) {
			log->error("Exiting. Can not create OpenGL 4.0 or 3.3 context. please update drivers and try again.");
			exit(1);
		}
	}

	std::mutex update_lock_step_cv_mutex;
	std::condition_variable update_lock_step_cv;

	OS::DetachContext(); // Must detach context in main thread, in order to attach it to other threads.

	std::jthread game_thread([&](const std::stop_token& stop_token) {
		using namespace rpg;
		Game game;
		graphics::RenderSystem render_system;
		double render_accumulator = 0;
		const double refresh_rate = os.GetMonitorRefreshRate();
		game.AddUpdateThread(UpdateThread(
				{[&](const double delta) {
					 log->info("Render update with {:0.6f} delta", delta);

					 render_accumulator += delta;
					 render_system.Update(delta);
					 if (render_accumulator >= 1.0 / refresh_rate) {
						 os.SwapBuffers();
						 log->info("Buffers swapped @ {} hz", refresh_rate);
						 render_accumulator = 0;
					 }
				 },
				 [&]() {
					 os.MakeCurrent();
					 render_system.Setup();
				 }}));
		game.AddUpdateThread(
				UpdateThread({[&](const double delta) { log->info("Physics update with {:0.6f} delta", delta); }}));
		game.AddUpdateThread(
				UpdateThread({[&](const double delta) { log->info("Sound update with {:0.6f} delta", delta); }}));
		game.Init();
		while (!stop_token.stop_requested()) {
			game.Update(os.GetDeltaTime());
			{
				std::unique_lock lk(update_lock_step_cv_mutex);
				update_lock_step_cv.notify_one();
			}
		}
	});

	while (!os.Closing()) {
		std::cout << "main_loop\n";
		os.OSMessageLoop();

		// Do main thread things here
		{
			using namespace std::chrono_literals;
			std::unique_lock lk(update_lock_step_cv_mutex);
			update_lock_step_cv.wait_for(lk, 500ms);
		}
	}

	game_thread.request_stop();
	game_thread.join();

	return 0;
}
