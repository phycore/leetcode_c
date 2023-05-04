#include "json_common.h"
#include <stdio.h>

// clang-format off
#define LOGI(...) printf(__VA_ARGS__); printf("\n");
#define LOGD(...) printf(__VA_ARGS__); printf("\n");
#define LOGE(...) printf(__VA_ARGS__); printf("\n");
// clang-format on

static int32_t JSON_dispatch_value_type(struct json_value_s* json_value);
static int32_t JSON_extract_elements(struct json_object_element_s* json_obj_element);

static int32_t JSON_dispatch_value_type(struct json_value_s* json_value) {
    int32_t retval = 0;

    uint32_t counter = 0;
    for (;;) {
        counter++;
        if (counter > 1) {
            LOGE("Exception!!! It have no json type.");
            retval = -1;
            break;
        }

        if (NULL == json_value) {
            LOGE("json_value is null.");
            retval = -1;
            break;
        }

        struct json_string_s* obj_string = json_value_as_string(json_value);
        if (NULL != obj_string) {
            LOGD("json_value = %s", obj_string->string);
            LOGD("json_value_length = %zd", obj_string->string_size);
            break;
        }

        struct json_number_s* obj_number = json_value_as_number(json_value);
        if (NULL != obj_number) {
            LOGD("json_value = %s", obj_number->number);
            LOGD("json_value_length = %zd", obj_number->number_size);
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
                LOGD("json_value array_idx = %zd in total length = %zd", arr_idx, arr_length);
                struct json_value_s* json_arr_value = (struct json_value_s*)arr_element->value;
                retval = JSON_dispatch_value_type(json_arr_value);
                arr_element = arr_element->next;
            }
            break;
        }

        if (json_value_is_true(json_value)) {
            LOGD("json_value is true.");
            break;
        }

        if (json_value_is_false(json_value)) {
            LOGD("json_value is false.");
            break;
        }

        if (json_value_is_null(json_value)) {
            LOGD("json_value is null.");
            break;
        }
    }

    return retval;
}

static int32_t JSON_extract_elements(struct json_object_element_s* json_obj_element) {
    int32_t retval = 0;
    if (NULL == json_obj_element) {
        LOGE("json_obj_element is null.");
        retval = -1;
        goto EXIT;
    }

    // extract key
    struct json_string_s* key = json_obj_element->name;
    // extract value
    struct json_value_s* json_value = json_obj_element->value;
    size_t json_type_of_value = json_value->type;
    LOGD("json_type = %zd; size of \"%s\" = %zd", json_type_of_value, key->string,
         key->string_size);
    // dispatch json value
    retval = JSON_dispatch_value_type(json_value);
    LOGD("JSON_dispatch_value_type retval = %d", retval);
    LOGD("\n");

EXIT:
    return retval;
}

void JSON_print_type(void) {
    LOGI("---JSON_TYPE_ENUM---");
    LOGI("json_type_string %d", json_type_string);
    LOGI("json_type_number %d", json_type_number);
    LOGI("json_type_object %d", json_type_object);
    LOGI("json_type_array  %d", json_type_array);
    LOGI("json_type_true   %d", json_type_true);
    LOGI("json_type_false  %d", json_type_false);
    LOGI("json_type_null   %d", json_type_null);
    LOGI("\n");
}

int32_t JSON_traverse_objects(struct json_object_s* json_object) {
    int32_t retval = 0;
    if (NULL == json_object) {
        LOGE("json_object is null.");
        retval = -1;
        goto EXIT;
    }

    size_t length_of_objects = json_object->length;
    struct json_object_element_s* obj_element = json_object->start;
    for (size_t obj_idx = 0; obj_idx < length_of_objects; obj_idx++) {
        LOGD("object idx = %zd in total length of json objects %zd", obj_idx, length_of_objects);
        retval = JSON_extract_elements(obj_element);
        obj_element = obj_element->next;
    }

EXIT:
    return retval;
}