function(set_warning_flag)
cmake_parse_arguments("SET_WARNING_FLAG" "" "TARGET" "" ${ARGN})
if (MSVC)
	set(WARNING_FLAG /W4)
else()
	set(WARNING_FLAG -Wall)
endif()
if (TARGET ${SET_WARNING_FLAG_TARGET})
	set_property(TARGET ${SET_WARNING_FLAG_TARGET} APPEND_STRING PROPERTY COMPILE_FLAGS ${WARNING_FLAG})
endif()
endfunction()

# Used by IDEs to nicely view header files
function(set_source_group_property)
cmake_parse_arguments("SET_SOURCE_GROUP_PROPERTY" "" "GROUP_NAME" "FILE_LIST" ${ARGN})

if (SET_SOURCE_GROUP_PROPERTY_GROUP_NAME)
	set(GROUP_NAME ${SET_SOURCE_GROUP_PROPERTY_GROUP_NAME})
else()
	set(GROUP_NAME Headers)
endif()

if (SET_SOURCE_GROUP_PROPERTY_FILE_LIST)
	source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX ${GROUP_NAME} FILES ${SET_SOURCE_GROUP_PROPERTY_FILE_LIST})
	set_property(SOURCE ${SET_SOURCE_GROUP_PROPERTY_FILE_LIST} PROPERTY HEADER_FILE_ONLY true)
endif()
endfunction()

# Consistent add_executable
function(add_program)
cmake_parse_arguments("ADD_PROGRAM" "" "TARGET" "FILE_LIST" ${ARGN})

add_executable(${ADD_PROGRAM_TARGET} ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp ${ADD_PROGRAM_FILE_LIST})
target_include_directories(${ADD_PROGRAM_TARGET} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
set_warning_flag(TARGET ${ADD_PROGRAM_TARGET})
link_common_lib(TARGET ${ADD_PROGRAM_TARGET})
endfunction()