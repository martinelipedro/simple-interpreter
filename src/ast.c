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
            break;
        }
        case AST_STRING:
        {
            ast->string = calloc(1, sizeof(ast_string));
            ast->string->value = (void*)0;
            ast->string->size = 0;
            break;
        }
        case AST_FUNCTION_CALL:
        {
            ast->funcion_call = calloc(1, sizeof(ast_function_call));
            ast->funcion_call->function_name = (void*)0;
            ast->funcion_call->arguments = (void*)0;
            break;
        }
        case AST_VARIABLE:
        {
            ast->variable = calloc(1, sizeof(ast_variable));
            ast->variable->name = (void*)0;
            break;
        }
        case AST_LITERAL_NUMBER:
        {
            ast->literal_number = calloc(1, sizeof(ast_literal_number));
            ast->literal_number->str = (void*)0;
            ast->literal_number->value = 0;
            break;
        }
        case AST_BINARY_EXPR:
        {
            ast->binary_expr = calloc(1, sizeof(ast_binary_expr));
            ast->binary_expr->lhs = (void*)0;
            ast->binary_expr->operator = 0;
            ast->binary_expr->rhs = (void*)0;
            break;
        }
    }

    return ast;
}