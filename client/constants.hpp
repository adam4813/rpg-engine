#pragma once

#include <string>

namespace rpg::config {

constexpr unsigned int WINDOW_WIDTH{800};
constexpr unsigned int WINDOW_HEIGHT{600};
inline std::string WINDOW_TITLE{"RPG Client 0.1"};

struct GL_VERSION_PAIR {
	int major;
	int minor;
};

constexpr GL_VERSION_PAIR PREFERRED_GL_VERSION{4, 0};
constexpr GL_VERSION_PAIR FALLBACK_GL_VERSION{3, 3};

} // namespace rpg::config
