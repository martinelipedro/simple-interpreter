#include "dynamic_array.h"
#include <stdio.h>

dynamic_array_T* init_dynamic_array(size_t element_size)
{
    dynamic_array_T* array = calloc(1, sizeof(struct DYNAMIC_ARRAY_STRUCT));

    array->values = (void*)0;
    array->len = 0;
    array->size = 0;
    array->element_size = element_size;
    array->it_current_index = 0;

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


void* dynamic_array_iterator_previous(dynamic_array_T* array)
{
    if (array->it_current_index == 0)
    {
        printf("[ERROR]: previous element doesn't exist [previous]");
        exit(1);
    }

    return array->values[array->it_current_index - 1];
}

void* dynamic_array_iterator_current(dynamic_array_T* array)
{
    return array->values[array->it_current_index];
}

void* dynamic_array_iterator_next(dynamic_array_T* array)
{
    if (array->it_current_index >= array->len - 1)
    {
        printf("[ERROR]: next element doesn't exist. [next]");
        exit(1);
    }

    return array->values[array->it_current_index + 1];
}

void dynamic_array_iterator_advance(dynamic_array_T* array)
{
    if (array->it_current_index >= array->len - 1)
    {
        printf("[ERROR]: next element doesn't exist. [advance]");
        exit(1);
    }

    array->it_current_index += 1;
}