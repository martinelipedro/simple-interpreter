#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "lexer.h"
#include "dynamic_array.h"



int main()
{
    dynamic_array_T* array = init_dynamic_array(sizeof(int*));


    int val1 = 56;
    int val2 = 78;

    dynamic_array_push(array, (void*)&val1);
    dynamic_array_push(array, (void*)&val2);


    dynamic_array_iterator_advance(array);
    printf("%d", *(int*)dynamic_array_iterator_current(array));
    printf("%d", *(int*)dynamic_array_iterator_previous(array));
}