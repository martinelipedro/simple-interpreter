#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdlib.h>

typedef struct DYNAMIC_ARRAY_STRUCT
{
    void** values;
    size_t element_size;
    size_t len;
    size_t size;
    size_t it_current_index;

} dynamic_array_T;

dynamic_array_T* init_dynamic_array(size_t element_size);
void dynamic_array_push(dynamic_array_T* array, void* element);
void* dynamic_array_get(dynamic_array_T* array, unsigned int index);

int dynamic_array_get_as_int(dynamic_array_T* array, unsigned int index);
int* dynamic_array_get_as_int_pointer(dynamic_array_T* array, unsigned int index);

void* dynamic_array_iterator_previous(dynamic_array_T* array);
void* dynamic_array_iterator_current(dynamic_array_T* array);
void* dynamic_array_iterator_next(dynamic_array_T* array);
void dynamic_array_iterator_advance(dynamic_array_T* array);


#endif