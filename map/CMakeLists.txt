list( APPEND
    MAP_LIB_OBJS
    src/map.c
    src/map_data.c
)

add_library(map STATIC ${MAP_LIB_OBJS})

target_include_directories(map
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/enc
)

target_include_directories(map
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/inc
)

target_link_libraries(map
    PUBLIC
        logging
)

if(MSVC)
    add_definitions("-D_CRT_SECURE_NO_WARNINGS")
endif()