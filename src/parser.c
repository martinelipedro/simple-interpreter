#include "parser.h"

parser_T* init_parser(dynamic_array_T* token_list)
{
    parser_T* parser = calloc(1, sizeof(struct PARSER_STRUCT));

    parser->token_list = token_list;
    parser->core_node = init_ast(AST_COMPOUND);

    return parser;
}

void parser_parse(parser_T* parser)
{
    parser->core_node = parser_parse_compound(parser);
}

ast_T* parser_parse_compound(parser_T* parser)
{

}