#include "ast.h"


ast_T* init_ast(int type)
{
    ast_T* ast = calloc(1, sizeof(struct AST_STRUCT));
    ast->type = type;

    switch (type)
    {
        case AST_COMPOUND:
        {
            ast->compound = init_dynamic_array(sizeof(struct AST_STRUCT));
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
    }

    return ast;
}