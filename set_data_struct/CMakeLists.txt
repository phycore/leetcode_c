list( APPEND
    SET_LIB_OBJS
    src/Set.c
    src/set_data.cpp
)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 11)

add_library(set_data_struct STATIC ${SET_LIB_OBJS})

target_include_directories(set_data_struct
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/enc
)

target_include_directories(set_data_struct
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/inc
)

target_link_libraries(set_data_struct
    PUBLIC
        logging
)