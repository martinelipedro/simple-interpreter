#include "builtin_functions.h"

#include <stdlib.h>
#include <stdio.h>

struct AST_STRUCT* builtin_function_print(visitor_T* visitor, ast_T* arguments)
{
    for (size_t i = 0; i < arguments->compound->len; i++)
    {
        ast_T* current_argument = visitor_visit(visitor, (ast_T*)arguments->compound->values[i]);

        switch (current_argument->type)
        {
            case AST_STRING: printf("%s\n", current_argument->string->value); break;
            default: printf("%p\n", current_argument);
        }
    }

    return init_ast(AST_NOOP);
}