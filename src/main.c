#include "parser.h"
#include "casters.h"

int main()
{
    lexer_T* lexer = init_lexer("hello = 'hello world'");
    lexer_collect_tokens(lexer);
    parser_T* parser = init_parser(lexer->token_list);
    parser_parse(parser);
}