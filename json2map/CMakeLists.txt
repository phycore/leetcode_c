list( APPEND
    JSON_MAP_LIB_OBJS
    src/json_2_map.c
    src/json_parsing_helper.c
    src/map_setting_helper.c
    src/vector_storing_helper.c
)

add_library(json_2_map STATIC ${JSON_MAP_LIB_OBJS})

target_include_directories(json_2_map
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/inc
)

target_include_directories(json_2_map
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/enc
)

target_link_libraries(json_2_map
    PUBLIC
        logging
        file_module
        map
        vector
)