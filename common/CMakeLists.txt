project(rpg-common)

find_package(Protobuf CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(asio CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(Bullet CONFIG REQUIRED)

file(GLOB ProtoFiles "${CMAKE_CURRENT_SOURCE_DIR}/proto/*.proto")
set_source_group_property(FILE_LIST ${ProtoFiles} GROUP_NAME Proto)
protobuf_generate_cpp(PROTO_SOURCES PROTO_HEADERS ${ProtoFiles})

set(rpg-common_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/test.cpp
	${PROTO_SOURCES}
)

set(rpg-common_SOURCES ${rpg-common_SOURCES} PARENT_SCOPE) # Add parent scope for test access

file(GLOB_RECURSE rpg-common_HEADERS LIST_DIRECTORIES false ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)
set_source_group_property(FILE_LIST ${rpg-common_HEADERS})

set(rpg-common_LIBRARY_NAME "common")
set(rpg-common_LIBRARY_NAME ${rpg-common_LIBRARY_NAME} PARENT_SCOPE)

add_library(${rpg-common_LIBRARY_NAME} STATIC ${rpg-common_SOURCES} ${rpg-common_HEADERS} ${ProtoFiles})

set_warning_flag(TARGET ${rpg-common_LIBRARY_NAME})

target_link_libraries(
	${rpg-common_LIBRARY_NAME}
	PUBLIC
	Bullet3Common BulletDynamics BulletCollision BulletSoftBody LinearMath
	protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite
	spdlog::spdlog spdlog::spdlog_header_only
	asio asio::asio
	glm::glm
)

target_include_directories(${rpg-common_LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${BULLET_INCLUDE_DIR})
