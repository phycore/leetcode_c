set(LOGGING_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_library(logging STATIC
    ${LOGGING_DIR}/src/log.c
)

target_include_directories(logging
    PUBLIC
        ${LOGGING_DIR}/enc
)

target_include_directories(logging
    PRIVATE
        ${LOGGING_DIR}/inc
)