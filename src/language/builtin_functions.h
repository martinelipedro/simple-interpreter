#ifndef BUILTIN_FUNCTIONS_H
#define BUILTIN_FUNCTIONS_H

#include "../ast.h"
#include "../visitor.h"

ast_T* builtin_function_print(visitor_T* visitor, ast_T* arguments);

#endif