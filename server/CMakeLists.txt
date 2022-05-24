project(rpg-server)

set(rpg-server_SOURCES # don't include main.cpp to keep it out of tests

)

set(rpg-server_SOURCES ${rpg-server_SOURCES} PARENT_SCOPE) # Add parent scope for test access

file(GLOB_RECURSE rpg-server_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.hpp)
set_source_group_property(FILE_LIST ${rpg-server_HEADERS})

if (WIN32)
	set(rpg-server_PROGRAM_NAME "rpg-server")
else ()
	set(rpg-server_PROGRAM_NAME "rpg-serverd")
endif ()

add_program(TARGET ${rpg-server_PROGRAM_NAME} FILE_LIST ${rpg-server_SOURCES} ${rpg-server_HEADERS})

