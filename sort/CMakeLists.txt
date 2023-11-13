list ( APPEND
    SORT_LIBS_OBJS
    src/sorting.c
    src/sorting_utils.c
)

add_library(sort STATIC ${SORT_LIBS_OBJS})

target_include_directories(sort
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/enc
)

target_include_directories(sort
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/inc
)

target_link_libraries(sort
    PUBLIC
        logging
)