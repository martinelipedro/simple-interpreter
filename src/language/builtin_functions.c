#include "builtin_functions.h"

#include <stdlib.h>
#include <stdio.h>

ast_T* builtin_function_print(visitor_T* visitor, ast_T* arguments)
{
    for (size_t i = 0; i < arguments->compound->len; i++)
    {
        ast_T* current_argument = visitor_visit(visitor, (ast_T*)arguments->compound->values[i]);

        switch (current_argument->type)
        {
            case AST_STRING: printf("%s\n", current_argument->string->value); break;
            case AST_LITERAL_NUMBER: printf("%f\n", current_argument->literal_number->value); break;
            case AST_VARIABLE: 
            {
                ast_T* variable = visitor_get_variable(visitor, current_argument->variable->name);
                if (variable->type == AST_STRING)
                {
                    printf("%s\n", variable->string->value);
                    break;
                }
                else if (variable->type == AST_LITERAL_NUMBER || variable->type == AST_BINARY_EXPR)
                {
                    printf("%f\n", visitor_visit(visitor, variable)->literal_number->value);
                    break;
                }
                break;

            }
            default: printf("%p\n", current_argument);
        }
    }

    return init_ast(AST_NOOP);
}