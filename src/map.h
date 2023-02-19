#ifndef MAP_H
#define MAP_H

#include <stdbool.h>
#include "dynamic_array.h"

#define KEY_STRING_SIZE 30

typedef struct MAP_STRUCT
{
    dynamic_array_T* keys;
    dynamic_array_T* values;
    size_t len;

} map_T;

map_T* init_map(size_t values_size);
void map_add(map_T* map, char* key, void* values);
void* map_get(map_T* map, char* key);
bool map_has_key(map_T* map, char* key);
bool map_is_empty(map_T* map);

#endif