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
ast_T* parser_parse_compound(parser_T* parser);

#endif