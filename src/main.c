#include "parser.h"
#include "casters.h"
#include "visitor.h"

#include <stdio.h>

int main()
{
    lexer_T* lexer = init_lexer("print('hello world', 'other?');");
    lexer_collect_tokens(lexer);
    parser_T* parser = init_parser(lexer->token_list);
    parser_parse(parser);

    visitor_T* visitor = init_visitor();
    visitor_visit(visitor, parser->core_node);    
}