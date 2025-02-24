cmake_minimum_required(VERSION 3.10)

project(leetcode_c)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

# Build type: Debug or Release
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

# Log level defined value defined by /logging/enc/log.h
set(LOG_LEVEL_DEBUG 1)
set(LOG_LEVEL_INFO 2)

# Build flag between Debug and Release
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("--Built: Debug build")
    add_compile_definitions(LOG_LEVEL=${LOG_LEVEL_DEBUG})
    add_definitions("-D_DEBUG_VERSION")
    if(MSVC)
        add_definitions("-D_CRTDBG_MAP_ALLOC")
    endif()
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    message("--Built: Release build")
    add_compile_definitions(LOG_LEVEL=${LOG_LEVEL_INFO})
    add_definitions("-D_RELEASE_VERSION")
endif()

# Operating system
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    message(STATUS "Configuring on/for Windows")
    set(OS_SYSTEM "windows")
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message(STATUS "Configuring on/for Linux")
    set(OS_SYSTEM "linux")
endif()

# Built main function or not.
set(LEETCODE_TESTS 1)
if(NOT DEFINED LEETCODE_TESTS)
set(LEETCODE_TESTS 0)
endif()

message(LEETCODE_TESTS=${LEETCODE_TESTS})

if(${LEETCODE_TESTS} EQUAL 1)
    add_subdirectory(main)
    add_subdirectory(array)
    add_subdirectory(linked_list)
    #add_subdirectory(json)
    add_subdirectory(logging)
    add_subdirectory(file_module)
    add_subdirectory(map)
    add_subdirectory(vector)
    add_subdirectory(json2map)
    add_subdirectory(cmd_invoke)
    add_subdirectory(problems_api)
    add_subdirectory(sort)
    add_subdirectory(plat_utility)
    add_subdirectory(problems_impl)
else()
    add_subdirectory(array)
    add_subdirectory(linked_list)
    #add_subdirectory(json)
    add_subdirectory(logging)
    add_subdirectory(file_module)
    add_subdirectory(map)
    add_subdirectory(vector)
    add_subdirectory(json2map)
    add_subdirectory(cmd_invoke)
    add_subdirectory(problems_api)
    add_subdirectory(sort)
    add_subdirectory(plat_utility)
    add_subdirectory(problems_impl)
endif()

# Unit Tests
set(UNIT_TESTS 1)
if(NOT DEFINED UNIT_TESTS)
    set(UNIT_TESTS 0)
endif()

if(${UNIT_TESTS} EQUAL 1)
    enable_testing()
    add_subdirectory(tests)
endif()