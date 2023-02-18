#include "dynamic_array.h"
#include <stdio.h>

dynamic_array_T* init_dynamic_array(size_t element_size)
{
    dynamic_array_T* array = calloc(1, sizeof(struct DYNAMIC_ARRAY_STRUCT));

    array->values = (void*)0;
    array->len = 0;
    array->size = 0;
    array->element_size = element_size;

    return array;
}

void dynamic_array_push(dynamic_array_T* array, void* element)
{
    array->len += 1;
    array->size = array->len * sizeof(array->element_size);
    if (array->len == 1)
    {
        array->values = calloc(1, sizeof(array->element_size));
        array->values[0] = element;
    }
    else
    {
        array->values = realloc(array->values, array->size);
        array->values[array->len - 1] = element;
    }
}

void* dynamic_array_get(dynamic_array_T* array, unsigned int index)
{
    if (index > (array->len - 1))
    {
        printf("[ERROR]: array index out of bounds.");
        exit(1);
    }

    return array->values[index];
}

int dynamic_array_get_as_int(dynamic_array_T* array, unsigned int index)
{
    return *(int*)(dynamic_array_get(array, index));
}

int* dynamic_array_get_as_int_pointer(dynamic_array_T* array, unsigned int index)
{
    return (int*)(dynamic_array_get(array, index));
}