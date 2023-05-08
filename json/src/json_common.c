#include "json_common.h"
#include "logging.h"
#include <stdio.h>
#include <stdlib.h>

static int32_t JSON_dispatch_value_type(struct json_value_s* json_value);
static int32_t JSON_extract_elements(struct json_object_element_s* json_obj_element);

static int32_t JSON_dispatch_value_type(struct json_value_s* json_value) {
    int32_t retval = 0;

    uint32_t counter = 0;
    for (;;) {
        counter++;
        if (counter > 1) {
            log_error("Exception!!! It have no json type.");
            retval = -1;
            break;
        }

        if (NULL == json_value) {
            log_error("json_value is null.");
            retval = -1;
            break;
        }

        struct json_string_s* obj_string = json_value_as_string(json_value);
        if (NULL != obj_string) {
            log_debug("json_value = %s", obj_string->string);
            log_debug("json_value_length = %zd", obj_string->string_size);
            break;
        }

        struct json_number_s* obj_number = json_value_as_number(json_value);
        if (NULL != obj_number) {
            log_debug("json_value = %s", obj_number->number);
            log_debug("json_value_length = %zd", obj_number->number_size);
            break;
        }

        struct json_object_s* obj = json_value_as_object(json_value);
        if (NULL != obj) {
            retval = JSON_traverse_objects(obj);
            break;
        }

        struct json_array_s* obj_arr = json_value_as_array(json_value);
        if (NULL != obj_arr) {
            struct json_array_element_s* arr_element = obj_arr->start;
            size_t arr_length = obj_arr->length;
            for (size_t arr_idx = 0; arr_idx < arr_length; arr_idx++) {
                log_debug("json_value array_idx = %zd in total length = %zd", arr_idx, arr_length);
                struct json_value_s* json_arr_value = (struct json_value_s*)arr_element->value;
                retval = JSON_dispatch_value_type(json_arr_value);
                arr_element = arr_element->next;
            }
            break;
        }

        if (json_value_is_true(json_value)) {
            log_debug("json_value is true.");
            break;
        }

        if (json_value_is_false(json_value)) {
            log_debug("json_value is false.");
            break;
        }

        if (json_value_is_null(json_value)) {
            log_debug("json_value is null.");
            break;
        }
    }

    return retval;
}

static int32_t JSON_extract_elements(struct json_object_element_s* json_obj_element) {
    int32_t retval = 0;
    if (NULL == json_obj_element) {
        log_error("json_obj_element is null.");
        retval = -1;
        goto EXIT;
    }

    // extract key
    struct json_string_s* key = json_obj_element->name;
    // extract value
    struct json_value_s* json_value = json_obj_element->value;
    size_t json_type_of_value = json_value->type;
    log_debug("json_type = %zd; size of \"%s\" = %zd", json_type_of_value, key->string,
              key->string_size);
    // dispatch json value
    retval = JSON_dispatch_value_type(json_value);
    log_debug("JSON_dispatch_value_type retval = %d", retval);
    log_debug("\n");

EXIT:
    return retval;
}

void JSON_print_type(void) {
    log_info("---JSON_TYPE_ENUM---");
    log_info("json_type_string %d", json_type_string);
    log_info("json_type_number %d", json_type_number);
    log_info("json_type_object %d", json_type_object);
    log_info("json_type_array  %d", json_type_array);
    log_info("json_type_true   %d", json_type_true);
    log_info("json_type_false  %d", json_type_false);
    log_info("json_type_null   %d", json_type_null);
    log_info("\n");
}

struct json_value_s* JSON_create_root(char* json_in_string, size_t str_length) {
    struct json_value_s* json_root = NULL;

    if (NULL == json_in_string || 0 == str_length) {
        log_error("Input json_in_string is null or string length is wrong.");
        goto EXIT;
    }

    size_t examine_length = strlen(json_in_string);
    if (examine_length != str_length) {
        log_warn("strlen(json_in_string) = %zd != str_length = %zd.", examine_length, str_length);
    }

    json_root = json_parse(json_in_string, str_length);
    if (NULL == json_root) {
        log_error("json_parse get root is fail.");
        goto EXIT;
    }

    log_info("json_root_type is %zd.", json_root->type);
    log_debug("Memory address of json_root = %p", json_root);

EXIT:
    return json_root;
}

int32_t JSON_free_root(struct json_value_s* json_root) {
    int32_t retval = -1;

    if (NULL != json_root) {
        log_debug("Memory address of json_root = %p", json_root);
        free(json_root);
        json_root = NULL;
        retval = 0;
    }

    return retval;
}

struct json_object_s* JSON_get_object(struct json_value_s* json_node) {
    struct json_object_s* json_object = NULL;

    if (NULL == json_node) {
        log_error("Input json_node is null.");
        goto EXIT;
    }

    json_object = json_value_as_object(json_node);
    if (NULL == json_object) {
        log_error("json_value_as_object of this node is fail.");
    }

EXIT:
    return json_object;
}

int32_t JSON_traverse_objects(struct json_object_s* json_object) {
    int32_t retval = 0;
    if (NULL == json_object) {
        log_error("json_object is null.");
        retval = -1;
        goto EXIT;
    }

    size_t length_of_objects = json_object->length;
    struct json_object_element_s* obj_element = json_object->start;
    for (size_t obj_idx = 0; obj_idx < length_of_objects; obj_idx++) {
        log_debug("object idx = %zd in total length of json objects %zd", obj_idx,
                  length_of_objects);
        retval = JSON_extract_elements(obj_element);
        obj_element = obj_element->next;
    }

EXIT:
    return retval;
}