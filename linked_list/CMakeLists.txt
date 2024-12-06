list( APPEND
    LINKED_LIST_LIB_OBJS
    src/Linked_List.c
)

add_library(linked_list STATIC ${LINKED_LIST_LIB_OBJS})

target_include_directories(linked_list
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/inc
)

target_link_libraries(linked_list
    PUBLIC
        logging
)