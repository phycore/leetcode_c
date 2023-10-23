#include "vector_storing_helper.h"

#include "log.h"
#include "vec.h"

static vec_str_t g_vector_str[MAX_SIZE_VEC];
static uint32_t g_occupied_str_index;
static uint32_t g_vector_str_opened;

static vec_int_t g_vector_int[MAX_SIZE_VEC];
static uint32_t g_occupied_int_index;
static uint32_t g_vector_int_opened;

static int32_t check_vector_type_valid(vec_type_t vec_type);
static int32_t check_out_of_memory(uint32_t index);
static int32_t check_buffer_overflow(uint32_t index);

static int32_t set_occupied_index(vec_type_t vec_type, uint32_t set_val);
static uint32_t get_occupied_index(vec_type_t vec_type);

static int32_t set_vector_opened(vec_type_t vec_type, uint32_t set_val);
static uint32_t get_vector_opened(vec_type_t vec_type);
static vec_str_t* get_vector_str(void);
static vec_int_t* get_vector_int(void);
static void* get_vector(vec_type_t vec_type);

static int32_t check_vector_type_valid(vec_type_t vec_type) {
    uint32_t retval = 1;

    switch (vec_type) {
        case VEC_TYPE_STR:
        case VEC_TYPE_INT:
            break;
        default:
            log_error("%s, it's not support type: %d.", __func__, vec_type);
            retval = 0;
            break;
    }

    return retval;
}

static int32_t check_out_of_memory(uint32_t index) { return (index >= MAX_SIZE_VEC) ? (1) : (0); }

static int32_t check_buffer_overflow(uint32_t index) { return check_out_of_memory(index); }

static int32_t set_occupied_index(vec_type_t vec_type, uint32_t set_val) {
    switch (vec_type) {
        case VEC_TYPE_STR:
            g_occupied_str_index = set_val;
            break;
        case VEC_TYPE_INT:
            g_occupied_int_index = set_val;
            break;
        default:
            break;
    }

    return VEC_STORING_SUCCESS;
}

static uint32_t get_occupied_index(vec_type_t vec_type) {
    uint32_t occupied_index = 0;
    switch (vec_type) {
        case VEC_TYPE_STR:
            occupied_index = g_occupied_str_index;
            break;
        case VEC_TYPE_INT:
            occupied_index = g_occupied_int_index;
            break;
        default:
            break;
    }

    return occupied_index;
}

static int32_t set_vector_opened(vec_type_t vec_type, uint32_t set_val) {
    switch (vec_type) {
        case VEC_TYPE_STR:
            g_vector_str_opened = set_val;
            break;
        case VEC_TYPE_INT:
            g_vector_int_opened = set_val;
            break;
        default:
            break;
    }

    return VEC_STORING_SUCCESS;
}

static uint32_t get_vector_opened(vec_type_t vec_type) {
    uint32_t opened = 0;
    switch (vec_type) {
        case VEC_TYPE_STR:
            opened = g_vector_str_opened;
            break;
        case VEC_TYPE_INT:
            opened = g_vector_int_opened;
            break;
        default:
            break;
    }

    return opened;
}

static vec_str_t* get_vector_str(void) {
    uint32_t occupied_index = get_occupied_index(VEC_TYPE_STR);
    uint32_t opened = get_vector_opened(VEC_TYPE_STR);
    if (1 != opened) {
        return NULL;
    }

    return (&g_vector_str[occupied_index]);
}

static vec_int_t* get_vector_int(void) {
    uint32_t occupied_index = get_occupied_index(VEC_TYPE_INT);
    uint32_t opened = get_vector_opened(VEC_TYPE_INT);
    if (1 != opened) {
        return NULL;
    }

    return (&g_vector_int[occupied_index]);
}

static void* get_vector(vec_type_t vec_type) {
    if (1 != check_vector_type_valid(vec_type)) {
        log_error("%s, error.", __func__);
    }

    switch (vec_type) {
        case VEC_TYPE_STR: {
            return (void*)get_vector_str();
        } break;

        case VEC_TYPE_INT: {
            return (void*)get_vector_int();
        } break;

        default: {
            return NULL;
        } break;
    }
}

int32_t init_vector_storing(void) {
    set_occupied_index(VEC_TYPE_STR, 0);
    set_occupied_index(VEC_TYPE_INT, 0);

    set_vector_opened(VEC_TYPE_STR, 0);
    set_vector_opened(VEC_TYPE_INT, 0);

    // Init vector.
    for (size_t index = 0; index < MAX_SIZE_VEC; index++) {
        vec_init(&g_vector_str[index]);
        vec_init(&g_vector_int[index]);
    }

    return VEC_STORING_SUCCESS;
}

int32_t uninit_vector_storing(void) {
    for (size_t index = 0; index < MAX_SIZE_VEC; index++) {
        vec_deinit(&g_vector_str[index]);
        vec_deinit(&g_vector_int[index]);
    }

    return VEC_STORING_SUCCESS;
}

void* allocate_vector(vec_type_t vec_type) {
    if (1 != check_vector_type_valid(vec_type)) {
        log_error("%s, error.", __func__);
        return NULL;
    }

    uint32_t occupied_index = get_occupied_index(vec_type);
    occupied_index += 1;
    if (1 == check_out_of_memory(occupied_index)) {
        log_error("%s, vec_type = %d, out of vector storing memory.", __func__, vec_type);
        return NULL;
    }

    set_occupied_index(vec_type, occupied_index);
    set_vector_opened(vec_type, 1);

    return get_vector(vec_type);
}

int32_t free_vector(vec_type_t vec_type) {
    vector_storing_return_t retval = VEC_STORING_SUCCESS;

    if (1 != check_vector_type_valid(vec_type)) {
        log_error("%s, error.", __func__);
        retval = VEC_STORING_NO_VEC_TYPE;
        goto EXIT;
    }

    retval = clear_vector(vec_type);
    if (VEC_STORING_SUCCESS != retval) {
        log_error("%s, error.", __func__);
        goto EXIT;
    }

    uint32_t occupied_index = get_occupied_index(vec_type);
    occupied_index -= 1;
    if (1 == check_buffer_overflow(occupied_index)) {
        log_warn(
            "%s, vec_type = %d occupied memory index = %d may overflow, force memory index to "
            "zero.",
            __func__, vec_type, occupied_index);
        occupied_index = 0;
    }

    set_occupied_index(vec_type, occupied_index);
    set_vector_opened(vec_type, 0);

EXIT:
    return retval;
}

int32_t clear_vector(vec_type_t vec_type) {
    vector_storing_return_t retval = VEC_STORING_SUCCESS;

    if (1 != check_vector_type_valid(vec_type)) {
        log_error("%s, error.", __func__);
        retval = VEC_STORING_NO_VEC_TYPE;
        goto EXIT;
    }

    uint32_t occupied_index = get_occupied_index(vec_type);
    if (1 == check_buffer_overflow(occupied_index)) {
        log_error("%s, will have buffer overflow.", __func__);
        retval = VEC_STORING_BUFFER_OVERFLOW;
        goto EXIT;
    }

    switch (vec_type) {
        case VEC_TYPE_STR:
            vec_clear(&g_vector_str[occupied_index]);
            break;

        case VEC_TYPE_INT:
            vec_clear(&g_vector_int[occupied_index]);
            break;

        default:
            break;
    }

EXIT:
    return retval;
}

int32_t push_vector(vec_type_t vec_type, void* push_value) {
    vector_storing_return_t retval = VEC_STORING_SUCCESS;

    if (1 != check_vector_type_valid(vec_type)) {
        log_error("%s, error.", __func__);
        retval = VEC_STORING_NO_VEC_TYPE;
        goto EXIT;
    }

    uint32_t occupied_index = get_occupied_index(vec_type);
    if (1 == check_buffer_overflow(occupied_index)) {
        log_error("%s, will have buffer overflow.", __func__);
        retval = VEC_STORING_BUFFER_OVERFLOW;
        goto EXIT;
    }

    uint32_t opened = get_vector_opened(vec_type);
    if (1 == opened) {
        switch (vec_type) {
            case VEC_TYPE_STR: {
                char* push_string = (char*)push_value;
                vec_push(&g_vector_str[occupied_index], push_string);
            } break;

            case VEC_TYPE_INT: {
                int* push_int = (int*)push_value;
                vec_push(&g_vector_int[occupied_index], *push_int);
            } break;

            default:
                break;
        }
    }

EXIT:
    return VEC_STORING_SUCCESS;
}