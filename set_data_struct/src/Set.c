#include "Set.h"
#include "logging.h"
#include "set_data.h"
#include <string.h>

int lengthOfLongestSubstring(char* s) { return 0; }

int set_test(char* s) {

    void* set_data = set_new();

    for (int idx = 0; idx < strlen(s); idx++) {
        log_debug("Set data add element: %c", *(s + idx));
        set_add_elmt(set_data, *(s + idx));
    }

    log_debug("The size of set = %d", set_get_size(set_data));

    set_print_all_elmts(set_data);

    set_delete(set_data);

    return 0;
}