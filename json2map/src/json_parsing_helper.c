#include "json_parsing_helper.h"

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


static struct json_value_s* new_json_root(char* json_in_string, size_t str_length);
static int32_t delete_json_root(struct json_value_s* json_root);

static void* get_json_type_value(json_type_t type_index, struct json_value_s* json_value);
static int get_json_type_int(json_type_t type_index, struct json_value_s* json_value);

static int32_t map_set_json_string(void* context, const char* key,
                                   struct json_string_s* json_string);
static int32_t map_set_json_number(void* context, const char* key,
                                   struct json_number_s* json_number);
static int32_t map_set_json_array(void* context, const char* key, struct json_array_s* json_array);
static int32_t map_set_json_true(void* context, const char* key, int true_value);
static int32_t map_set_json_null(void* context, const char* key);
static int32_t map_set_json_value(void* context, struct json_string_s* json_key,
                                  struct json_value_s* json_value);

static int32_t extract_elemnts_to_map(void* context, struct json_object_element_s* obj_element);
static int32_t traverse_all_elements(void* context, struct json_object_s* json_object);

static struct json_value_s* new_json_root(char* json_in_string, size_t str_length) {
    struct json_value_s* json_root = NULL;

    if (NULL == json_in_string || 0 == str_length) {
        log_error("%s, Input json_in_string is null or string length is wrong.", __func__);
        goto EXIT;
    }

    size_t examine_length = strlen(json_in_string);
    if (examine_length != str_length) {
        log_warn("strlen(json_in_string) = %zd != str_length = %zd.", examine_length, str_length);
    }

    json_root = json_parse(json_in_string, str_length);
    if (NULL == json_root) {
        log_error("%s, json_parse get root is fail.", __func__);
        goto EXIT;
    }

    log_info("%s, json_root_type is %zd.", __func__, json_root->type);

EXIT:
    return json_root;
}

static int32_t delete_json_root(struct json_value_s* json_root) {
    json_parsing_helper_return_t retval = JSON_PARSING_HELPER_SUCCESS;
    IS_NULL(json_root, "json_root is null!", JSON_PARSING_HELPER_ROOT_NULL);

    free(json_root);
    json_root = NULL;

    return retval;
}

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
    IS_NULL(json_value, "json value is null!", JSON_PARSING_HELPER_PARSING_FAIL);

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
    IS_NULL(json_string, "json_string is null!", JSON_PARSING_HELPER_MAP_SET_FAIL);
    json_parsing_helper_return_t retval = JSON_PARSING_HELPER_SUCCESS;

    char* value = (char*)json_string->string;
    retval = map_data_set_str(context, key, value);
    log_debug("%s, key = %s, value = %s", __func__, key, value);

    if (JSON_PARSING_HELPER_SUCCESS != retval) {
        retval = JSON_PARSING_HELPER_MAP_SET_FAIL;
    }

    return retval;
}

static int32_t map_set_json_number(void* context, const char* key,
                                   struct json_number_s* json_number) {
    IS_NULL(json_number, "json_number is null!", JSON_PARSING_HELPER_MAP_SET_FAIL);
    json_parsing_helper_return_t retval = JSON_PARSING_HELPER_SUCCESS;

    int value = atoi(json_number->number);
    retval = map_data_set_int(context, key, value);
    log_debug("%s, key = %s, value = %d", __func__, key, value);

    if (JSON_PARSING_HELPER_SUCCESS != retval) {
        retval = JSON_PARSING_HELPER_MAP_SET_FAIL;
    }

    return retval;
}

static int32_t map_set_json_array(void* context, const char* key, struct json_array_s* json_array) {
    IS_NULL(json_array, "json_array is null!", JSON_PARSING_HELPER_MAP_SET_FAIL);
    json_parsing_helper_return_t retval = JSON_PARSING_HELPER_SUCCESS;

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
            retval = JSON_PARSING_HELPER_PARSING_FAIL;
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
    json_parsing_helper_return_t retval = JSON_PARSING_HELPER_SUCCESS;

    retval = map_data_set_int(context, key, true_value);
    log_debug("%s, key = %s, value = %d", __func__, key, true_value);

    if (JSON_PARSING_HELPER_SUCCESS != retval) {
        retval = JSON_PARSING_HELPER_MAP_SET_FAIL;
    }

    return retval;
}

static int32_t map_set_json_null(void* context, const char* key) {
    json_parsing_helper_return_t retval = JSON_PARSING_HELPER_SUCCESS;

    retval = map_data_set_str(context, key, "null");
    log_debug("%s, key = %s, value = null", __func__, key);

    if (JSON_PARSING_HELPER_SUCCESS != retval) {
        retval = JSON_PARSING_HELPER_MAP_SET_FAIL;
    }

    return retval;
}

static int32_t map_set_json_value(void* context, struct json_string_s* json_key,
                                  struct json_value_s* json_value) {
    json_parsing_helper_return_t retval = JSON_PARSING_HELPER_SUCCESS;
    IS_NULL(context, "Map context is null!", JSON_PARSING_HELPER_CONTEXT_NULL);
    IS_NULL(json_key, "json string key is null!", JSON_PARSING_HELPER_PARSING_FAIL);
    IS_NULL(json_value, "json value is null!", JSON_PARSING_HELPER_PARSING_FAIL);

    json_type_t type_index = json_value->type;
    void* json_value_buffer = get_json_type_value(type_index, json_value);
    int json_value_int = get_json_type_int(type_index, json_value);
    if (NULL == json_value_buffer && 0 == json_value_int) {
        log_error("%s, there is no json type!", __func__);
        retval = JSON_PARSING_HELPER_NO_JSON_TYPE;
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
            retval = JSON_PARSING_HELPER_NO_JSON_TYPE;
        } break;
    }

EXIT:
    return retval;
}

static int32_t extract_elemnts_to_map(void* context, struct json_object_element_s* obj_element) {
    json_parsing_helper_return_t retval = JSON_PARSING_HELPER_SUCCESS;
    IS_NULL(context, "Map context is null!", JSON_PARSING_HELPER_CONTEXT_NULL);
    IS_NULL(obj_element, "json object is null!", JSON_PARSING_HELPER_PARSING_FAIL);

    // extract key
    struct json_string_s* json_key = obj_element->name;
    // extract value
    struct json_value_s* json_value = obj_element->value;

    retval = map_set_json_value(context, json_key, json_value);

    return retval;
}

static int32_t traverse_all_elements(void* context, struct json_object_s* json_object) {
    json_parsing_helper_return_t retval = JSON_PARSING_HELPER_SUCCESS;
    IS_NULL(context, "Map context is null!", JSON_PARSING_HELPER_CONTEXT_NULL);
    IS_NULL(json_object, "json object is null!", JSON_PARSING_HELPER_PARSING_FAIL);

    size_t length_of_objects = json_object->length;
    struct json_object_element_s* obj_element = json_object->start;
    for (size_t obj_idx = 0; obj_idx < length_of_objects; obj_idx++) {
        log_debug("%s, object idx = %zd in total length %zd of json objects.", __func__, obj_idx,
                  length_of_objects);
        retval = extract_elemnts_to_map(context, obj_element);
        if (JSON_PARSING_HELPER_SUCCESS != retval) {
            log_error("%s, fail!", __func__);
            break;
        }
        obj_element = obj_element->next;
    }

    return retval;
}

int32_t json_parsing_save_map(void* context, struct json_value_s* json_root) {
    json_parsing_helper_return_t retval = JSON_PARSING_HELPER_SUCCESS;
    IS_NULL(context, "Map context is null!", JSON_PARSING_HELPER_CONTEXT_NULL);
    IS_NULL(json_root, "json_root is null!", JSON_PARSING_HELPER_ROOT_NULL);

    struct json_object_s* json_object = json_value_as_object(json_root);
    if (NULL == json_object) {
        retval = JSON_PARSING_HELPER_PARSING_FAIL;
        log_error("%s, json_value_as_object of this json node is fail!", __func__);
        goto EXIT;
    }

    retval = traverse_all_elements(context, json_object);
EXIT:
    return retval;
}

struct json_value_s* init_json_parsing(char* json_in_string, size_t str_length) {
    struct json_value_s* json_root = new_json_root(json_in_string, str_length);

    return json_root;
}

int32_t uninit_json_parsing(struct json_value_s* json_root) {
    delete_json_root(json_root);

    return 0;
}