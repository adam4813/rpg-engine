enable_testing()
find_package(GTest CONFIG REQUIRED)
include(GoogleTest)

set(rpg-test_SOURCES
	sanity_test.cpp
)

set(rpg-test_PROGRAM_NAME "tests")

add_executable(${rpg-test_PROGRAM_NAME} ${rpg-test_SOURCES} ${rpg-server_SOURCES} ${rpg-client_SOURCES})

set_warning_flag(TARGET ${rpg-test_PROGRAM_NAME})

link_common_lib(TARGET ${rpg-test_PROGRAM_NAME})
link_client_libs(TARGET ${rpg-test_PROGRAM_NAME})

target_include_directories(${rpg-test_PROGRAM_NAME} PUBLIC ${rpg-client_SOURCE_DIR} ${rpg-server_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${rpg-test_PROGRAM_NAME} PRIVATE GTest::gtest GTest::gtest_main)

gtest_discover_tests(${rpg-test_PROGRAM_NAME})
