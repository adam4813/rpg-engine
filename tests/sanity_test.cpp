#include <gtest/gtest.h>

#include <asio.hpp>
#include <btBulletDynamicsCommon.h>
#include <glm/glm.hpp>
#include <spdlog/spdlog.h>

#include <components.pb.h>

#include <test.hpp>

#ifndef __APPLE__
#include <GL/glew.h>
#endif

#ifdef WIN32
#include <GL/wglew.h>
#endif

#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#endif
#include <GLFW/glfw3.h>
#include <al.h>
#include <alc.h>
#include <imgui.h>

#include <client.hpp>

TEST(SanityCheck, OneEqOne) { EXPECT_EQ(1, 1); }
