list( APPEND
    PROBLEMS_IMPL_LIB_OBJS
    src/problems_cimpl.c
)

add_library(prob_impl STATIC ${PROBLEMS_IMPL_LIB_OBJS})

target_include_directories(prob_impl
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/enc
)

target_include_directories(prob_impl
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/inc
)

target_link_libraries(prob_impl
    PUBLIC
        logging
)

if(MSVC)
    add_definitions("-D_CRT_SECURE_NO_WARNINGS")
endif()