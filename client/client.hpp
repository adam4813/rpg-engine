#pragma once

#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#endif
#include <GLFW/glfw3.h>

#include <al.h>
#include <alc.h>
#include <imgui.h>

#include <client.hpp>

namespace rpg {
class Client {};
} // namespace rpg