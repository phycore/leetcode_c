cmake_minimum_required(VERSION 3.10)

project(leetcode_c)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

if(NOT DEFINED LEETCODE_TESTS)
set(LEETCODE_TESTS 0)
endif()

message(LEETCODE_TESTS=${LEETCODE_TESTS})

if(${LEETCODE_TESTS} EQUAL 1)
    add_subdirectory(main)
    add_subdirectory(array)
    add_subdirectory(linked_list)
else()
    add_subdirectory(array)
    add_subdirectory(linked_list)
endif()