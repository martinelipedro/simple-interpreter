#include "parser.h"

#include <string.h>
#include <stdio.h>


#define mark printf("HERE!");

parser_T* init_parser(dynamic_array_T* token_list)
{
    parser_T* parser = calloc(1, sizeof(struct PARSER_STRUCT));

    parser->token_list = token_list;
    parser->core_node = (void*)0;

    return parser;
}

void parser_parse(parser_T* parser)
{
    parser->core_node = parser_parse_compound(parser);
}

ast_T* parser_parse_statement(parser_T* parser)
{
    switch (parser_current(parser)->type)
    {
        case TOK_ID: return parser_parse_id(parser); break;
        case TOK_STRING: return parser_parse_string(parser); break;
    }
}

ast_T* parser_parse_compound(parser_T* parser)
{
    ast_T* compound = init_ast(AST_COMPOUND);
    dynamic_array_push(compound->compound, (void*)parser_parse_statement(parser));

    while (parser_current(parser)->type == TOK_SEMI)
    {
        dynamic_array_push(compound->compound, (void*)parser_parse_statement(parser));
    }

    return compound;
}

ast_T* parser_parse_id(parser_T* parser)
{
    if (parser_next(parser)->type == TOK_EQUALS)
    {
        return parser_parse_variable_definition(parser);
    }
}


ast_T* parser_parse_variable_definition(parser_T* parser)
{
    ast_T* vardef_ast = init_ast(AST_VARIABLE_DEFINITION);

    vardef_ast->variable_definition->name = parser_eat(parser, TOK_ID)->value;
    parser_eat(parser, TOK_EQUALS);
    vardef_ast->variable_definition->value = parser_parse_statement(parser);

    return vardef_ast;
}

ast_T* parser_parse_string(parser_T* parser)
{
    ast_T* string_ast = init_ast(AST_STRING);

    string_ast->string->value = parser_eat(parser, TOK_STRING)->value;
    string_ast->string->size = strlen(string_ast->string->value);

    return string_ast;
}

token_T* parser_previous(parser_T* parser)
{
    return (token_T*)dynamic_array_iterator_previous(parser->token_list); 
}

token_T* parser_current(parser_T* parser)
{
    return (token_T*)dynamic_array_iterator_current(parser->token_list); 

}

token_T* parser_next(parser_T* parser)
{
    return (token_T*)dynamic_array_iterator_next(parser->token_list); 

}

token_T* parser_advance(parser_T* parser)
{
    dynamic_array_iterator_advance(parser->token_list); 
    return parser_current(parser);
}

token_T* parser_eat(parser_T* parser, int type)
{
    token_T* token = parser_current(parser);
    if (token->type != type)
    {
        printf("[ERROR]: unexpected token. expecting %d", type);
        exit(1);
    }

    (void)!parser_advance(parser);
    return token;
}