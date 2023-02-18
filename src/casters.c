#include "casters.h"

int as_int(void* value)
{
    return *(int*)value;
}

int* as_int_ptr(void* value)
{
    return (int*)value;
}