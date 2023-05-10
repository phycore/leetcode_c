cmake_minimum_required(VERSION 3.10)

project(main_leetcode)

set(MAIN_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(main_leetcode
    ${MAIN_DIR}/src/main.c
)

target_include_directories(main_leetcode
    PRIVATE
        ${MAIN_DIR}/inc
)

target_link_libraries(main_leetcode
    PRIVATE
        json
        logging
)

add_dependencies(main_leetcode json logging)