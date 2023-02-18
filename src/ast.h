#ifndef AST_H
#define AST_H

#include "lexer.h"

struct AST_STRUCT;

/* AST NODES */
typedef dynamic_array_T ast_compound;
typedef struct 
{
    char* name;
    struct AST_STRUCT* value;
} ast_variable_definition;

typedef struct AST_STRUCT
{   
    enum 
    {
        AST_COMPOUND,
        AST_VARIABLE_DEFINITION,

    } type;

    ast_compound* compound;
    ast_variable_definition* variable_definition;

} ast_T;

ast_T* init_ast(int type);



#endif