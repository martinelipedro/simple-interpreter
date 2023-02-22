#ifndef VISITOR_H
#define VISITOR_H


#include "map.h"
#include "ast.h"


typedef struct VISITOR_STRUCT
{
    map_T* variables;

} visitor_T;


visitor_T* init_visitor();

ast_T* visitor_visit(visitor_T* visitor, ast_T* node);

ast_T* visitor_visit_compound(visitor_T* visitor, ast_T* node);
ast_T* visitor_visit_variable_definition(visitor_T* visitor, ast_T* node);
ast_T* visitor_visit_string(visitor_T* visitor, ast_T* node);
ast_T* visitor_visit_function_call(visitor_T* visitor, ast_T* node);
ast_T* visitor_visit_variable(visitor_T* visitor, ast_T* node);
ast_T* visitor_visit_binary_expr(visitor_T* visitor, ast_T* node);
ast_T* visitor_visit_literal_number(visitor_T* visitor, ast_T* node);

void visitor_set_variable(visitor_T* visitor, ast_T* variable);
ast_T* visitor_get_variable(visitor_T* visitor, char* variable_name);


#endif