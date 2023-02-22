#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "parser.h"

typedef struct PARSER_STRUCT
{
    dynamic_array_T* token_list;
    ast_T* core_node;

} parser_T;

parser_T* init_parser(dynamic_array_T* token_list);

void parser_parse(parser_T* parser);
ast_T* parser_parse_statement(parser_T* parser);
ast_T* parser_parse_compound(parser_T* parser);
ast_T* parser_parse_id(parser_T* parser);
ast_T* parser_parse_variable_definition(parser_T* parser);
ast_T* parser_parse_string(parser_T* parser);
ast_T* parser_parse_function_call(parser_T* parser);
ast_T* parser_parse_function_call_arguments(parser_T* parser);
ast_T* parser_parse_variable(parser_T* parser);

ast_T* parser_parse_expr(parser_T* parser);
ast_T* parser_parse_term(parser_T* parser);
ast_T* parser_parse_fator(parser_T* parser);

token_T* parser_previous(parser_T* parser);
token_T* parser_current(parser_T* parser);
token_T* parser_next(parser_T* parser);
token_T* parser_advance(parser_T* parser);
token_T* parser_eat(parser_T* parser, int type);

#endif