#include "parser.h"

#include <stdio.h>

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
    if (parser_current(parser)->type == TOK_ID)
    {
        ast_T* test = init_ast(AST_VARIABLE_DEFINITION);
        ast_T* var_val = init_ast(AST_STRING);

        var_val->string->size = 2;
        var_val->string->value = "value";

        test->variable_definition->name = "hello";
        test->variable_definition->value = var_val;

        return test;
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