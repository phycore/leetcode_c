#include "json_parsing_helper.h"

#include "log.h"
#include "map_setting_helper.h"

#define IS_NULL(x, message, status) \
    do {                            \
        if (NULL == x) {            \
            log_error(message);     \
            return status;          \
        }                           \
    } while (0)

static traverse_callback_fn g_callback_fn;

static struct json_value_s* new_json_root(char* json_in_string, size_t str_length);
static int32_t delete_json_root(struct json_value_s* json_root);

static int32_t extract_elemnts_to_map(void* context, struct json_object_element_s* obj_element);
static int32_t traverse_nodes(void* context, struct json_object_s* json_object);

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

    log_debug("%s, json_root_type is %zd.", __func__, json_root->type);

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

static int32_t extract_elemnts_to_map(void* context, struct json_object_element_s* obj_element) {
    json_parsing_helper_return_t retval = JSON_PARSING_HELPER_SUCCESS;
    IS_NULL(context, "Map context is null!", JSON_PARSING_HELPER_CONTEXT_NULL);
    IS_NULL(obj_element, "json object is null!", JSON_PARSING_HELPER_PARSING_FAIL);

    // extract key
    struct json_string_s* json_key = obj_element->name;
    // extract value
    struct json_value_s* json_value = obj_element->value;

    retval = map_set_json_value(context, json_key, json_value, g_callback_fn);

    return retval;
}

static int32_t traverse_nodes(void* context, struct json_object_s* json_object) {
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

    retval = traverse_nodes(context, json_object);
EXIT:
    return retval;
}

struct json_value_s* init_json_parsing(char* json_in_string, size_t str_length) {
    g_callback_fn = traverse_nodes;
    struct json_value_s* json_root = new_json_root(json_in_string, str_length);

    return json_root;
}

int32_t uninit_json_parsing(struct json_value_s* json_root) {
    g_callback_fn = NULL;
    delete_json_root(json_root);

    return 0;
}