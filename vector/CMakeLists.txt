list( APPEND
    VEC_LIBS_OBJS
    src/vec.c
)

add_library(vector STATIC ${VEC_LIBS_OBJS})

target_include_directories(vector
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/inc
)

target_link_libraries(vector
    PUBLIC
        logging
)