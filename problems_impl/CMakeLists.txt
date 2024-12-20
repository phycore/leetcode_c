list( APPEND
    PROBLEMS_IMPL_LIB_OBJS
    src/problems_wrapper.c
    src/problems_impl.cpp
)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 11)

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