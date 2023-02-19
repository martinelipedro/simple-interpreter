#include "visitor.h"

#include <stdio.h>


visitor_T* init_visitor()
{
    visitor_T* visitor = calloc(1, sizeof(struct VISITOR_STRUCT));
    visitor->variables = init_map(sizeof(ast_T*));

    return visitor;
}

ast_T* visitor_visit(visitor_T* visitor, ast_T* node)
{
    switch (node->type)
    {
        case AST_COMPOUND: return visitor_visit_compound(visitor, node); break;
        case AST_VARIABLE_DEFINITION: return visitor_visit_variable_definition(visitor, node); break;
    }

    printf("[ERROR]: Statement of type %d doesn't exist.", node->type);
    exit(1);
}

ast_T* visitor_visit_compound(visitor_T* visitor, ast_T* node)
{
    for (size_t i = 0; i < node->compound->len; i++)
    {
        visitor_visit(visitor, dynamic_array_get(node->compound, i));
    }

    return init_ast(AST_NOOP);
}

ast_T* visitor_visit_variable_definition(visitor_T* visitor, ast_T* node)
{
    map_add(visitor->variables, node->variable_definition->name, (void*)node->variable_definition->value);
    return node;
}