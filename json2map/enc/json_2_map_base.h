#ifndef _JSON_2_MAP_BASE_H
#define _JSON_2_MAP_BASE_H

#define JSON_2_MAP_BASE_VER "0.1.0"

#define IJSON_2_MAP_MODULE_BASE(iface)                                                    \
    int32_t (*init)(struct iface * p_iface);                                              \
    int32_t (*uninit)(struct iface * p_iface);                                            \
    int32_t (*make_instance)(struct iface * p_iface, void* buffer, uint32_t buffer_size); \
    int32_t (*get_base_version)(struct iface * p_iface, char* base_version);              \
    int32_t (*get_components_version)(struct iface * p_iface, int32_t component_type,     \
                                      char* lib_version);                                 \
    int32_t (*map_get_all_keys)(struct iface * p_iface, char* keys, uint32_t key_length); \
    int32_t (*map_get_int)(struct iface * p_iface, char* key, int32_t* get_integer);      \
    int32_t (*map_get_char)(struct iface * p_iface, char* key, char* get_char);           \
    int32_t (*map_get_string)(struct iface * p_iface, char* key, char* get_str);          \
    int32_t (*map_get_float)(struct iface * p_iface, char* key, float* get_float);        \
    int32_t (*map_get_double)(struct iface * p_iface, char* key, double* get_double);     \
    void* (*map_get_vector_int)(struct iface * p_iface, char* key);                       \
    void* (*map_get_vector_str)(struct iface * p_iface, char* key)

#endif  // _JSON_2_MAP_BASE_H