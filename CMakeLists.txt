cmake_minimum_required(VERSION 3.19)
project(rpg VERSION 0.1)
enable_testing()

option(BUILD_DOCS "Build documentation" OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
	add_definitions(-DPROTOBUF_USE_DLLS -D_CRT_SECURE_NO_WARNINGS -D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS -D_WIN32_WINNT=0x0601 -DWIN32_LEAN_AND_MEAN)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4125") # Auto generated protobuf gives lots of these on msvc
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:__cplusplus") # MSVC define __cplusplus workaround

	if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
		add_compile_options(/EHsc)
		add_definitions(-DWIN32)
	endif()
	# Only MSVC compiler understands these flags
	if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
		# The following turns off warnings in external libraries until the generator respects include_directories(SYSTEM ...) see https://devblogs.microsoft.com/cppblog/broken-warnings-theory/
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /experimental:external /external:anglebrackets /external:W0")
	endif()
endif()

include(cmake/helpers.cmake)
include(cmake/link_helpers.cmake)

add_subdirectory(common)
add_subdirectory(client)
add_subdirectory(server)
add_subdirectory(tests)

if (BUILD_DOCS)
	add_subdirectory(docs_targets)
endif()
