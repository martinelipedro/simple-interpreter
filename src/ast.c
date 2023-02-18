#include "ast.h"


ast_T* init_ast(int type)
{
    ast_T* ast = calloc(1, sizeof(struct AST_STRUCT));

    ast->type = type;

    ast->compound = init_dynamic_array(sizeof(struct AST_STRUCT));

    ast->variable_definition->name = (void*)0;
    ast->variable_definition->value = (void*)0;

    return ast;
}