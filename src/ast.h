#ifndef AST_H
#define AST_H

#include "lexer.h"

typedef struct AST_STRUCT ast_T;

/* AST NODES */
typedef dynamic_array_T ast_compound;

typedef struct
{
    char* value;
    size_t size;

} ast_string;

typedef struct 
{
    char* name;
    ast_T* value;
} ast_variable_definition;

typedef struct
{
    char* function_name;
    ast_T* arguments;

} ast_function_call;

typedef struct
{
    char* name;

} ast_variable;

typedef struct
{
    char* str;
    float value;

} ast_literal_number;

typedef struct
{
    ast_T* lhs;
    token_T* operator;
    ast_T* rhs;

} ast_binary_expr;

typedef struct AST_STRUCT
{   
    enum 
    {
        AST_NOOP,
        AST_COMPOUND,
        AST_VARIABLE_DEFINITION,
        AST_STRING,
        AST_FUNCTION_CALL,
        AST_VARIABLE,
        AST_LITERAL_NUMBER,
        AST_BINARY_EXPR,

    } type;

    ast_compound* compound;
    ast_variable_definition* variable_definition;
    ast_string* string;
    ast_function_call* funcion_call;
    ast_variable* variable;
    ast_literal_number* literal_number;
    ast_binary_expr* binary_expr;

} ast_T;

ast_T* init_ast(int type);



#endif