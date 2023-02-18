#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdlib.h>

typedef struct DYNAMIC_ARRAY_STRUCT
{
    void** values;
    size_t element_size;
    size_t len;
    size_t size;

} dynamic_array_T;

dynamic_array_T* init_dynamic_array(size_t element_size);
void dynamic_array_push(dynamic_array_T* array, void* element);
void* dynamic_array_get(dynamic_array_T* array, unsigned int index);

int dynamic_array_get_as_int(dynamic_array_T* array, unsigned int index);
int* dynamic_array_get_as_int_pointer(dynamic_array_T* array, unsigned int index);

#endif