#include "visitor.h"

#include <stdio.h>
#include <string.h>

#include "language/builtin_functions.h"


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
        case AST_STRING: return visitor_visit_string(visitor, node); break;
        case AST_FUNCTION_CALL: return visitor_visit_function_call(visitor, node); break;
        case AST_VARIABLE: return visitor_visit_variable(visitor, node); break;
        case AST_BINARY_EXPR: return visitor_visit_binary_expr(visitor, node); break;
        case AST_LITERAL_NUMBER: return visitor_visit_literal_number(visitor, node);
        case AST_NOOP: return init_ast(AST_NOOP); break;

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
    visitor_set_variable(visitor, node);
    return node;
}

ast_T* visitor_visit_string(visitor_T* visitor, ast_T* node)
{
    return node;
}

ast_T* visitor_visit_function_call(visitor_T* visitor, ast_T* node)
{
    if (strcmp(node->funcion_call->function_name, "print") == 0)
    {
        return builtin_function_print(visitor, node->funcion_call->arguments);
    }

    printf("[ERROR]: Method not found.");
    exit(1);
}

ast_T* visitor_visit_variable(visitor_T* visitor, ast_T* node)
{
    if (map_has_key(visitor->variables, node->variable->name))
    {
        return node;
    }

    printf("[ERROR]: Variable: %s not found.", node->variable->name);
    exit(1);
}


ast_T* visitor_visit_binary_expr(visitor_T* visitor, ast_T* node)
{
    switch (node->binary_expr->operator)
    {
        case TOK_PLUS:
        {
            ast_T* result = init_ast(AST_LITERAL_NUMBER);
            result->literal_number->value 
                = visitor_visit(visitor, node->binary_expr->lhs)->literal_number->value
                + visitor_visit(visitor, node->binary_expr->rhs)->literal_number->value;
            
            return result;
            break;
        }
        case TOK_MINUS:
        {
            ast_T* result = init_ast(AST_LITERAL_NUMBER);
            result->literal_number->value 
                = visitor_visit(visitor, node->binary_expr->lhs)->literal_number->value
                - visitor_visit(visitor, node->binary_expr->rhs)->literal_number->value;
            
            return result;
            break;
        }
        case TOK_STAR:
        {
            ast_T* result = init_ast(AST_LITERAL_NUMBER);
            result->literal_number->value 
                = visitor_visit(visitor, node->binary_expr->lhs)->literal_number->value
                * visitor_visit(visitor, node->binary_expr->rhs)->literal_number->value;
            
            return result;
            break;
        }
        case TOK_SLASH:
        {
            ast_T* result = init_ast(AST_LITERAL_NUMBER);
            result->literal_number->value 
                = visitor_visit(visitor, node->binary_expr->lhs)->literal_number->value
                / visitor_visit(visitor, node->binary_expr->rhs)->literal_number->value;
            
            return result;
            break;
        }
    }
}

ast_T* visitor_visit_literal_number(visitor_T* visitor, ast_T* node)
{
    return node;
}

void visitor_set_variable(visitor_T* visitor, ast_T* node)
{
    map_add(visitor->variables, node->variable_definition->name, (void*)node->variable_definition->value);
}

ast_T* visitor_get_variable(visitor_T* visitor, char* variable_name)
{
    return (ast_T*)map_get(visitor->variables, variable_name);
}