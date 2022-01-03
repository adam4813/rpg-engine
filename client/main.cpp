#include <iostream>
#include <test.hpp>

#include "os/os.hpp"
#include <spdlog/sinks/stdout_sinks.h>

auto InitializeLogger(spdlog::level::level_enum log_level) {
	std::vector<spdlog::sink_ptr> sinks;
	sinks.push_back(std::make_shared<spdlog::sinks::stdout_sink_mt>());
	auto log = std::make_shared<spdlog::logger>("console_log", begin(sinks), end(sinks));
	log->set_level(log_level);
	log->set_pattern("%v"); // [%l] [thread %t] %v"); // Format on stdout
	spdlog::register_logger(log);
	return log;
}

int main(int argc, char const* argv[]) {

	rpg::os::OS os;
	std::cout << "Hello client world!" << std::endl;

	auto log = InitializeLogger(spdlog::level::debug);

	const unsigned int window_width = 800;
	const unsigned int window_height = 600;
	std::string window_title = "RPG Client 0.1";

	log->info("Initializing OpenGL...");
	if (!os.InitializeWindow(window_width, window_height, window_title, 4, 0)) {
		log->warn("The OpenGL 4.0 context wasn't created properly, attempting fallback");
		if (!os.InitializeWindow(window_width, window_height, window_title, 3, 3)) {
			log->error("Exiting. Can not create OpenGL 4.0 or 3.3 context. please update drivers and try again.");
			exit(1);
		}
	}

	while (!os.Closing()) {
		os.OSMessageLoop();
	}

	return 0;
}
