#ifndef _SET_DATA_H
#define _SET_DATA_H

#ifdef __cplusplus
extern "C" {
#endif

void* set_new(void);
int set_delete(void* context);

int set_add_elmt(void* context, char element_ch);
int set_erase_elmt(void* context, char element_ch);
int set_has_elmt(void* context, char element_ch);
int set_print_all_elmts(void* context);
int set_get_size(void* context);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _SET_DATA_H