list( APPEND
    JSON_LIB_OBJS
    src/json_common.c
)

add_library(json STATIC ${JSON_LIB_OBJS})

target_include_directories(json
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/inc
)

target_link_libraries(json
    PUBLIC
        logging
)