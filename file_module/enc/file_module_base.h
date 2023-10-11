#ifndef _FILE_MODULE_BASE_H
#define _FILE_MODULE_BASE_H

#define FILE_HANDLE_BASE_VER "0.1.0"

#define IFILE_HANDLE_BASE(iface)                                                             \
    int32_t (*init)(struct iface * p_iface);                                                 \
    int32_t (*uninit)(struct iface * p_iface);                                               \
    int32_t (*make_instance)(struct iface * p_iface, const char* file_path,                  \
                             const int32_t operation_mode);                                  \
    int32_t (*get_base_version)(struct iface * p_iface, char* base_version);                 \
    int32_t (*get_string)(struct iface * p_iface, int32_t str_type, char* get_string);       \
    int32_t (*get_integer)(struct iface * p_iface, int32_t int_type, int32_t * get_integer); \
    int32_t (*get_buffer)(struct iface * p_iface, int32_t buff_type, uint8_t * buffer,       \
                          uint32_t * buffer_size)

#endif