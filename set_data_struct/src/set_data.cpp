#include <iostream>
#include <set>
#include <set_data.h>

using namespace std;

typedef struct set_data {
    std::set<char> set_ch;
} set_data_t;

void* set_new(void) {
    set_data_t* set_data = new set_data_t;
    // Create an empty set.
    set_data->set_ch = {};

    return set_data;
}

int set_delete(void* context) {
    set_data_t* set_data = (set_data_t*)context;
    // Clear set.
    set_data->set_ch.clear();
    delete set_data;

    return 0;
}

int set_add_elmt(void* context, char element_ch) {
    set_data_t* set_data = (set_data_t*)context;

    set_data->set_ch.insert(element_ch);

    return 0;
}

int set_erase_elmt(void* context, char element_ch) {
    set_data_t* set_data = (set_data_t*)context;

    set_data->set_ch.erase(element_ch);

    return 0;
}

int set_has_elmt(void* context, char element_ch) {
    set_data_t* set_data = (set_data_t*)context;

    return (int)(set_data->set_ch.count(element_ch));
}

int set_print_all_elmts(void* context) {
    set_data_t* set_data = (set_data_t*)context;

    for (auto it = set_data->set_ch.begin(); it != set_data->set_ch.end(); it++) {
        std::cout << *it << std::endl;
    }

    return 0;
}

int set_get_size(void* context) {
    set_data_t* set_data = (set_data_t*)context;

    return (int)(set_data->set_ch.size());
}