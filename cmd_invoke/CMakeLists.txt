set(CMD_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_library(cmd_invoke STATIC
    ${CMD_DIR}/src/cmd_invoke.c
    ${CMD_DIR}/src/mem_utils.c
)

target_include_directories(cmd_invoke
    PRIVATE
    ${CMD_DIR}/inc
)

target_include_directories(cmd_invoke
    PUBLIC
    ${CMD_DIR}/enc
)

target_link_libraries(cmd_invoke
    PUBLIC
        json_2_map
        logging
)