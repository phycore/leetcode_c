list( APPEND
    ARRAY_LIB_OBJS
    src/Array.c
)

add_library(array STATIC ${ARRAY_LIB_OBJS})

target_include_directories(array
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/inc
)