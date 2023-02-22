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
        case TOK_NUMBER: return parser_parse_expr(parser); break;
        default: 
        {
            parser_advance(parser);
            return init_ast(AST_NOOP); 
            break;
        }
    }
}

ast_T* parser_parse_compound(parser_T* parser)
{
    ast_T* compound = init_ast(AST_COMPOUND);
    dynamic_array_push(compound->compound, (void*)parser_parse_statement(parser));

    while (parser_current(parser)->type == TOK_SEMI)
    {
        parser_eat(parser, TOK_SEMI);
        dynamic_array_push(compound->compound, (void*)parser_parse_statement(parser));
    }

    return compound;
}

ast_T* parser_parse_id(parser_T* parser)
{
    
    switch (parser_next(parser)->type)
    {
        case TOK_EQUALS: return parser_parse_variable_definition(parser); break;
        case TOK_LPAREN: return parser_parse_function_call(parser); break;
        default: return parser_parse_variable(parser); break;
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

ast_T* parser_parse_function_call(parser_T* parser)
{
    ast_T* funcall_ast = init_ast(AST_FUNCTION_CALL);

    funcall_ast->funcion_call->function_name = parser_eat(parser, TOK_ID)->value;

    parser_eat(parser, TOK_LPAREN);

    if (parser_next(parser)->type != TOK_LPAREN)
    {
        funcall_ast->funcion_call->arguments = parser_parse_function_call_arguments(parser);
    }
    else
    {
        funcall_ast->funcion_call->arguments = init_ast(AST_NOOP);
    }

    return funcall_ast;
}

ast_T* parser_parse_function_call_arguments(parser_T* parser)
{
    ast_T* arguments_ast = init_ast(AST_COMPOUND);

    dynamic_array_push(arguments_ast->compound, parser_parse_statement(parser));

    while (parser_current(parser)->type == TOK_COMMA)
    {
        parser_eat(parser, TOK_COMMA);
        dynamic_array_push(arguments_ast->compound, parser_parse_statement(parser));
    }

    parser_eat(parser, TOK_RPAREN);

    return arguments_ast;
}

ast_T* parser_parse_variable(parser_T* parser)
{
    ast_T* variable_ast = init_ast(AST_VARIABLE);
    variable_ast->variable->name = parser_eat(parser, TOK_ID)->value;
    return variable_ast;
}


ast_T* parser_parse_expr(parser_T* parser)
{
    ast_T* node = parser_parse_term(parser);

    

    while (parser_current(parser)->type == TOK_PLUS || parser_current(parser)->type == TOK_MINUS)
    {
        if (parser_current(parser)->type == TOK_PLUS)
        {
            parser_eat(parser, TOK_PLUS);

            ast_T* new_node = init_ast(AST_BINARY_EXPR);
            new_node->binary_expr->lhs = node;
            new_node->binary_expr->operator = TOK_PLUS;
            new_node->binary_expr->rhs = parser_parse_term(parser);
            return new_node;
        }
        else
        {
            parser_eat(parser, TOK_MINUS);
            ast_T* new_node = init_ast(AST_BINARY_EXPR);
            new_node->binary_expr->lhs = node;
            new_node->binary_expr->operator = TOK_MINUS;
            new_node->binary_expr->rhs = parser_parse_term(parser);
            return new_node;
        }   
    }

    return node;
}

ast_T* parser_parse_term(parser_T* parser)
{
    ast_T* node = parser_parse_factor(parser);

    while (parser_current(parser)->type == TOK_STAR || parser_current(parser)->type == TOK_SLASH)
    {
        if (parser_current(parser)->type == TOK_STAR)
        {
            parser_eat(parser, TOK_STAR);
            ast_T* new_node = init_ast(AST_BINARY_EXPR);
            new_node->binary_expr->lhs = node;
            new_node->binary_expr->operator = TOK_STAR;
            new_node->binary_expr->rhs = parser_parse_factor(parser);
            return new_node;
        }
        else
        {
            parser_eat(parser, TOK_SLASH);
            ast_T* new_node = init_ast(AST_BINARY_EXPR);
            new_node->binary_expr->lhs = node;
            new_node->binary_expr->operator = TOK_SLASH;
            new_node->binary_expr->rhs = parser_parse_factor(parser);
            return new_node;
        }   
    }

    return node;
}

ast_T* parser_parse_factor(parser_T* parser)
{
    token_T* token = parser_current(parser);

    switch (token->type)
    {
        case TOK_NUMBER: 
        {
            ast_T* ast_number = init_ast(AST_LITERAL_NUMBER);
            ast_number->literal_number->str = token->value;
            ast_number->literal_number->value = atoi(token->value);
            parser_eat(parser, TOK_NUMBER);
            return ast_number;
            break;
        }
    }
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