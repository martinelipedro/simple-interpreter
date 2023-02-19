#include "ast.h"


ast_T* init_ast(int type)
{
    ast_T* ast = calloc(1, sizeof(struct AST_STRUCT));
    ast->type = type;

    switch (type)
    {
        case AST_COMPOUND:
        {
            ast->compound = init_dynamic_array(sizeof(ast_compound));
            break;
        }
        case AST_VARIABLE_DEFINITION:
        {
            ast->variable_definition = calloc(1, sizeof(ast_variable_definition));
            ast->variable_definition->name = (void*)0;
            ast->variable_definition->value = (void*)0;
        }
        case AST_STRING:
        {
            ast->string = calloc(1, sizeof(ast_string));
            ast->string->value = (void*)0;
            ast->string->size = 0;
        }
        case AST_FUNCTION_CALL:
        {
            ast->funcion_call = calloc(1, sizeof(ast_function_call));
            ast->funcion_call->function_name = (void*)0;
            ast->funcion_call->arguments = (void*)0;
        }
    }

    return ast;
}