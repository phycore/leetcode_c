#ifndef _MAP_COMMON_H
#define _MAP_COMMON_H

// clang-format off
typedef enum {
    MAP_DATA_SUCCESS       = 0,
    MAP_DATA_CONTEXT_NULL  = 1,
    MAP_DATA_KEY_NULL      = 2,
    MAP_DATA_VALUE_NULL    = 3,
    MAP_DATA_NO_KEY        = 4,
    MAP_DATA_OUT_OF_MEMORY = 5,
} map_data_return_t;
// clang-format on

void* create_map_data(int ID);
int destroy_map_data(void* context);

int map_data_set_void_pointer(void* context, char* key, void* value);
void* map_data_get_void_pointer(void* context, char* key);

int map_data_set_str(void* context, char* key, char* value);
int map_data_get_str(void* context, char* key, char* value);

int map_data_set_int(void* context, char* key, const int value);
int map_data_get_int(void* context, char* key, int* value);

int map_data_set_char(void* context, char* key, const char value);
int map_data_get_char(void* context, char* key, char* value);

int map_data_set_float(void* context, char* key, const float value);
int map_data_get_float(void* context, char* key, float* value);

int map_data_set_double(void* context, char* key, const double value);
int map_data_get_double(void* context, char* key, double* value);

int map_data_remove_key(void* context, char* key);

#endif  // _MAP_COMMON_H