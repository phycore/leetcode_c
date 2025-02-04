if (CMAKE_CXX_BYTE_ORDER STREQUAL "BIG_ENDIAN")
    message(STATUS "CXX: Big endian.")
    add_compile_definitions(IS_BIG_ENDIAN=1)
else()
    message(STATUS "CXX: Little endian")
    add_compile_definitions(IS_BIG_ENDIAN=0)
endif()

list(APPEND
    COMPRESS_LIBS_OBJS
    src/compress.c
)

add_library(compress STATIC ${COMPRESS_LIBS_OBJS})

target_include_directories(compress
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/enc
)