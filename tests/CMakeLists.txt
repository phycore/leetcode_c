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
)

add_dependencies(main_leetcode json logging)

add_test(NAME LeetcodeTests COMMAND main_leetcode -j ${MAIN_DIR}/TwoSum_case_1.json)
#add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --verbose)
#list(APPEND CMAKE_CTEST_ARGUMENTS "--output-on-failure")