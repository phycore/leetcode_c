cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(unit_test)

### Sleep Time Unit Tests ###
add_executable(main_time
    ${CMAKE_CURRENT_SOURCE_DIR}/time/main.c
)

target_link_libraries(main_time
    PUBLIC
        plat_utility
)

foreach(SECS RANGE 0 5 1)
    # SECS = [0, 1, 2, 3, 4, 5]
    message(STATUS "time sleep test ${SECS} seconds.")
    add_test(
        NAME timeout_test_${SECS}
        COMMAND main_time -t "${SECS}"
    )
    MATH(EXPR TIMEOUT_SECS "${SECS} + 1")
    message(STATUS "check timeout ${TIMEOUT_SECS} seconds.")
    set_tests_properties(timeout_test_${SECS} PROPERTIES TIMEOUT ${TIMEOUT_SECS})
endforeach()
### Sleep Time Unit Tests ###