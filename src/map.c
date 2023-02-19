#include "map.h"

#include <stdio.h>
#include <string.h>

map_T* init_map(size_t values_size)
{
    map_T* map = calloc(1, sizeof(struct MAP_STRUCT));

    map->keys = init_dynamic_array(KEY_STRING_SIZE * sizeof(char));
    map->values = init_dynamic_array(values_size);
    map->len = 0;

    return map;
}

void map_add(map_T* map, char* key, void* values)
{
    dynamic_array_push(map->keys, (void*)key);
    dynamic_array_push(map->values, (void*)values);
    map->len += 1;
}

void* map_get(map_T* map, char* key)
{
    for (size_t i = 0; i < map->len; i++)
    {
        if (strcmp((char*)map->keys->values[i], key) == 0)
        {
            return map->values->values[i];
        }
    }

    printf("[ERROR]: Value not found in map.");
    exit(1);
}

bool map_has_key(map_T* map, char* key)
{
    for (size_t i = 0; i < map->len; i++)
    {
        if (strcmp((char*)map->keys->values[i], key) == 0)
        {
            return true;
        }
    }

    return false;
}

bool map_is_empty(map_T* map)
{
    if (map->len == 0)
    {
        return true;
    }

    return false;
}