project(rpg-server)

set(rpg-server_SOURCES # don't include main.cpp to keep it out of tests

)

set(rpg-server_SOURCES ${rpg-server_SOURCES} PARENT_SCOPE) # Add parent scope for test access

file(GLOB_RECURSE rpg-server_HEADERS LIST_DIRECTORIES false ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)
set_source_group_property(FILE_GLOB ${rpg-server_HEADERS})

if (WIN32)
	set(rpg-server_PROGRAM_NAME "rpg-server")
else ()
	set(rpg-server_PROGRAM_NAME "rpg-serverd")
endif ()

add_executable(${rpg-server_PROGRAM_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp ${rpg-server_SOURCES} ${rpg-server_HEADERS})

set_warning_flag(TARGET ${rpg-server_PROGRAM_NAME})

link_common_lib(TARGET ${rpg-server_PROGRAM_NAME})
