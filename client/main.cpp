#include <iostream>
#include <test.hpp>

#include "constants.hpp"
#include "game.hpp"
#include "os/os.hpp"
#include <spdlog/sinks/stdout_sinks.h>

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

	rpg::os::OS os;

	using namespace rpg::config;
	log->info("Initializing OpenGL...");
	if (!os.InitializeWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE)) {
		log->warn("The OpenGL 4.0 context wasn't created properly, attempting fallback");
		if (!os.InitializeWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, FALLBACK_GL_VERSION)) {
			log->error("Exiting. Can not create OpenGL 4.0 or 3.3 context. please update drivers and try again.");
			exit(1);
		}
	}

	std::mutex m;
	std::condition_variable cv;
	os.DetachContext();

	std::thread game_thread([&]() {
		using rpg::UpdateThread;
		rpg::Game game;
		game.AddUpdateThread(UpdateThread::Create(
				[&](const double delta) {
					std::stringstream ss;
					ss << "Render update @ " << delta << std::endl;
					std::cout << ss.str();
					os.SwapBuffers();
				},
				[&]() { os.MakeCurrent(); }));
		game.AddUpdateThread(UpdateThread::Create([](const double delta) {
			std::stringstream ss;
			ss << "Physics update @ " << delta << std::endl;
			std::cout << ss.str();
		}));
		game.AddUpdateThread(UpdateThread::Create([](const double delta) {
			std::stringstream ss;
			ss << "Sound update @ " << delta << std::endl;
			std::cout << ss.str();
		}));
		game.Init();
		while (!os.Closing()) {
			game.Update(os.GetDeltaTime());

			std::unique_lock lk(m);
			cv.notify_one();
		}
	});

	while (!os.Closing()) {
		std::cout << "main_loop\n";
		os.OSMessageLoop();

		// Do main thread things here

		std::unique_lock lk(m);
		cv.wait(lk);
	}

	game_thread.join();

	return 0;
}
