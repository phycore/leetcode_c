set(PROB_API_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_library(problems_api STATIC
    ${PROB_API_DIR}/src/do_problems_api.c
)

target_include_directories(problems_api
    PRIVATE
    ${PROB_API_DIR}/inc
)

target_include_directories(problems_api
    PUBLIC
    ${PROB_API_DIR}/enc
)

target_link_libraries(problems_api
    PUBLIC
        json_2_map
        vector
        array
        linked_list
        sort
        logging
)