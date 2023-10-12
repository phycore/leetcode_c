list( APPEND
    MAP_LIB_OBJS
    src/map.c
)

add_library(map STATIC ${MAP_LIB_OBJS})

target_include_directories(map
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/inc
)

target_link_libraries(map
    PUBLIC
        logging
)