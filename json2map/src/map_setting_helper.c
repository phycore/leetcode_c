#include "map_setting_helper.h"

#include "log.h"
#include "map_data.h"
#include "vec.h"

#define IS_NULL(x, message, status) \
    do {                            \
        if (NULL == x) {            \
            log_error(message);     \
            return status;          \
        }                           \
    } while (0)

#define init_vector(vec)                                           \
    do {                                                           \
        vec_init(&vec);                                            \
        log_debug("init_vector, length of list = %d", vec.length); \
    } while (0)

#define deinit_vector(vec)                                           \
    do {                                                             \
        vec_deinit(&vec);                                            \
        log_debug("deinit_vector, length of list = %d", vec.length); \
    } while (0)

typedef void* (*json_value_type_fn)(struct json_value_s* const);
typedef int (*json_value_int_fn)(struct json_value_s* const);

static json_value_type_fn g_json_value_type_fn[] = {
    json_value_as_string,
    json_value_as_number,
    json_value_as_object,
    json_value_as_array,
};

static json_value_int_fn g_json_value_int_fn[] = {
    json_value_is_true,
    json_value_is_false,
    json_value_is_null,
};

static void* get_json_type_value(json_type_t type_index, struct json_value_s* json_value);
static int get_json_type_int(json_type_t type_index, struct json_value_s* json_value);

static int32_t map_set_json_string(void* context, const char* key,
                                   struct json_string_s* json_string);
static int32_t map_set_json_number(void* context, const char* key,
                                   struct json_number_s* json_number);
static int32_t map_set_json_array(void* context, const char* key, struct json_array_s* json_array);
static int32_t map_set_json_true(void* context, const char* key, int true_value);
static int32_t map_set_json_null(void* context, const char* key);

static void* get_json_type_value(json_type_t type_index, struct json_value_s* json_value) {
    IS_NULL(json_value, "json value is null!", NULL);

    switch (type_index) {
        case json_type_string:
        case json_type_number:
        case json_type_object:
        case json_type_array: {
            return g_json_value_type_fn[type_index](json_value);
        } break;

        default: {
            return NULL;
        } break;
    }
}

static int get_json_type_int(json_type_t type_index, struct json_value_s* json_value) {
    IS_NULL(json_value, "json value is null!", MAP_SETTING_HELPER_JSON_VALUE_NULL);

    switch (type_index) {
        case json_type_true:
        case json_type_false:
        case json_type_null: {
            // json_type_ture is an offset.
            int fn_index = (type_index - json_type_true);
            return g_json_value_int_fn[fn_index](json_value);
        } break;

        default: {
            return 0;
        } break;
    }
}

static int32_t map_set_json_string(void* context, const char* key,
                                   struct json_string_s* json_string) {
    IS_NULL(json_string, "json_string is null!", MAP_SETTING_HELPER_FAIL);
    map_setting_helper_return_t retval = MAP_SETTING_HELPER_SUCCESS;

    char* value = (char*)json_string->string;
    retval = map_data_set_str(context, key, value);
    log_debug("%s, key = %s, value = %s", __func__, key, value);

    if (MAP_SETTING_HELPER_SUCCESS != retval) {
        retval = MAP_SETTING_HELPER_FAIL;
    }

    return retval;
}

static int32_t map_set_json_number(void* context, const char* key,
                                   struct json_number_s* json_number) {
    IS_NULL(json_number, "json_number is null!", MAP_SETTING_HELPER_FAIL);
    map_setting_helper_return_t retval = MAP_SETTING_HELPER_SUCCESS;

    int value = atoi(json_number->number);
    retval = map_data_set_int(context, key, value);
    log_debug("%s, key = %s, value = %d", __func__, key, value);

    if (MAP_SETTING_HELPER_SUCCESS != retval) {
        retval = MAP_SETTING_HELPER_FAIL;
    }

    return retval;
}

static int32_t map_set_json_array(void* context, const char* key, struct json_array_s* json_array) {
    IS_NULL(json_array, "json_array is null!", MAP_SETTING_HELPER_FAIL);
    map_setting_helper_return_t retval = MAP_SETTING_HELPER_SUCCESS;

    vec_int_t list_int = {0};
    vec_str_t list_str = {0};
    init_vector(list_int);
    init_vector(list_str);

    struct json_array_element_s* arr_element = json_array->start;
    size_t arr_length = json_array->length;

    json_type_t type_index = 0;
    void* json_value_buff = NULL;
    for (size_t arr_idx = 0; arr_idx < arr_length; arr_idx++) {
        log_debug("json_value array_idx = %zd in total length = %zd", arr_idx, arr_length);

        struct json_value_s* json_arr_value = (struct json_value_s*)arr_element->value;
        type_index = json_arr_value->type;
        json_value_buff = get_json_type_value(type_index, json_arr_value);

        if (json_type_string == type_index) {
            struct json_string_s* obj_string = (struct json_string_s*)json_value_buff;
            vec_push(&list_str, (char*)obj_string->string);
        } else if (json_type_number == type_index) {
            struct json_number_s* obj_number = (struct json_number_s*)json_value_buff;
            vec_push(&list_int, atoi(obj_number->number));
        } else if (json_type_true == type_index) {
            vec_push(&list_int, 1);
        } else if (json_type_false == type_index) {
            vec_push(&list_int, 0);
        } else {
            log_error("%s, not support vector type!", __func__);
            retval = MAP_SETTING_HELPER_NO_JSON_TYPE;
            break;
        }

        json_value_buff = NULL;
        arr_element = arr_element->next;
    }

    if (list_str.length > 0) {
        map_data_set_void_pointer(context, key, (void*)&list_str);
        int index = 0;
        char* value = NULL;
        vec_foreach(&list_str, value, index) {
            log_debug("%s, key = %s, value[%d] = %s", __func__, key, index, value);
        }
    }

    if (list_int.length > 0) {
        map_data_set_void_pointer(context, key, (void*)&list_int);
        int index = 0;
        int value = 0;
        vec_foreach(&list_int, value, index) {
            log_debug("%s, key = %s, value[%d] = %d", __func__, key, index, value);
        }
    }

    deinit_vector(list_int);
    deinit_vector(list_str);

    return retval;
}

static int32_t map_set_json_true(void* context, const char* key, int true_value) {
    map_setting_helper_return_t retval = MAP_SETTING_HELPER_SUCCESS;

    retval = map_data_set_int(context, key, true_value);
    log_debug("%s, key = %s, value = %d", __func__, key, true_value);

    if (MAP_SETTING_HELPER_SUCCESS != retval) {
        retval = MAP_SETTING_HELPER_FAIL;
    }

    return retval;
}

static int32_t map_set_json_null(void* context, const char* key) {
    map_setting_helper_return_t retval = MAP_SETTING_HELPER_SUCCESS;

    retval = map_data_set_str(context, key, "null");
    log_debug("%s, key = %s, value = null", __func__, key);

    if (MAP_SETTING_HELPER_SUCCESS != retval) {
        retval = MAP_SETTING_HELPER_FAIL;
    }

    return retval;
}

static int32_t map_set_json_value(void* context, struct json_string_s* json_key,
                                  struct json_value_s* json_value) {
    map_setting_helper_return_t retval = MAP_SETTING_HELPER_SUCCESS;
    IS_NULL(context, "Map context is null!", MAP_SETTING_HELPER_CONTEXT_NULL);
    IS_NULL(json_key, "json string key is null!", MAP_SETTING_HELPER_JSON_KEY_NULL);
    IS_NULL(json_value, "json value is null!", MAP_SETTING_HELPER_JSON_VALUE_NULL);

    json_type_t type_index = json_value->type;
    void* json_value_buffer = get_json_type_value(type_index, json_value);
    int json_value_int = get_json_type_int(type_index, json_value);
    if (NULL == json_value_buffer && 0 == json_value_int) {
        log_error("%s, there is no json type!", __func__);
        retval = MAP_SETTING_HELPER_NO_JSON_TYPE;
        goto EXIT;
    }

    switch (type_index) {
        case json_type_string: {
            struct json_string_s* obj_string = (struct json_string_s*)json_value_buffer;
            retval = map_set_json_string(context, json_key->string, obj_string);
        } break;

        case json_type_number: {
            struct json_number_s* obj_number = (struct json_number_s*)json_value_buffer;
            retval = map_set_json_number(context, json_key->string, obj_number);
        } break;

        case json_type_object: {
            struct json_object_s* obj = (struct json_object_s*)json_value_buffer;
            retval = traverse_all_elements(context, obj);
        } break;

        case json_type_array: {
            struct json_array_s* obj_arr = (struct json_array_s*)json_value_buffer;
            retval = map_set_json_array(context, json_key->string, obj_arr);
        } break;

        case json_type_true: {
            retval = map_set_json_true(context, json_key->string, 1);
        } break;

        case json_type_false: {
            retval = map_set_json_true(context, json_key->string, 0);
        } break;

        case json_type_null: {
            retval = map_set_json_null(context, json_key->string);
        } break;

        default: {
            log_error("%s, Invalid json_type.", __func__);
            retval = MAP_SETTING_HELPER_NO_JSON_TYPE;
        } break;
    }

EXIT:
    return retval;
}