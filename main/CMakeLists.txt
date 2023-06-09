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

if(MSVC)
    add_definitions("-D_CRT_SECURE_NO_WARNINGS")
endif()

target_link_libraries(main_leetcode
    PRIVATE
        json
        logging
        set_data_struct
)

add_dependencies(main_leetcode json logging set_data_struct)