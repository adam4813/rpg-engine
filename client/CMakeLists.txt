project(rpg-client)

set(rpg-client_SOURCES # don't include main.cpp to keep it out of tests
	${CMAKE_CURRENT_SOURCE_DIR}/graphics/render-system.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/os/os.cpp
	"${CMAKE_CURRENT_SOURCE_DIR}/os/os-event-handler.cpp"
	${CMAKE_CURRENT_SOURCE_DIR}/game.cpp
)
set(rpg-client_SOURCES ${rpg-client_SOURCES} PARENT_SCOPE) # Add parent scope for test access

file(GLOB_RECURSE rpg-client_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.hpp)
set_source_group_property(FILE_LIST ${rpg-client_HEADERS})

IF (APPLE)
	EXEC_PROGRAM(uname ARGS -v OUTPUT_VARIABLE DARWIN_VERSION)
	STRING(REGEX MATCH "[0-9]+" DARWIN_VERSION ${DARWIN_VERSION})

	IF (DARWIN_VERSION LESS 20)
		# No longer needed as of 11.0.1, see issue #179
		set(OSX_LIBRARIES "/usr/lib/libobjc.dylib")
	ENDIF (DARWIN_VERSION LESS 20)

	# Rather wonderfully, Apple decided to mark every single fucking OpenGL function
	# as deprecated because they have 'deprecated' OpenGL. Brilliant!
	add_definitions(-DGL_SILENCE_DEPRECATION)
elseif (UNIX AND NOT APPLE)
	find_package(X11 REQUIRED)
ENDIF(APPLE)

set(rpg-client_PROGRAM_NAME "rpg-client")

add_program(TARGET ${rpg-client_PROGRAM_NAME} FILE_LIST ${rpg-client_SOURCES} ${rpg-client_HEADERS})
link_client_libs(TARGET ${rpg-client_PROGRAM_NAME})
