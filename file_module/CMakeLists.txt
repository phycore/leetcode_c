list( APPEND
    FILE_M_LIB_OBJS
    src/file_module.c
    src/file_utils.c
)

add_library(file_module STATIC ${FILE_M_LIB_OBJS})

target_include_directories(file_module
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/inc
)

target_include_directories(file_module
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/enc
)

target_link_libraries(file_module
    PUBLIC
        logging
)

if(MSVC)
    add_definitions("-D_CRT_SECURE_NO_WARNINGS")
endif()