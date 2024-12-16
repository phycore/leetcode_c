list( APPEND
    PLAT_UTILITY_LIB_OBJS
    src/plat_time_${OS_SYSTEM}.c
)

add_library(plat_utility STATIC ${PLAT_UTILITY_LIB_OBJS})

target_include_directories(plat_utility
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/enc
)