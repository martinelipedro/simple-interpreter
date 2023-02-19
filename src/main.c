#include "parser.h"
#include "casters.h"

#include <stdio.h>

int main()
{
    lexer_T* lexer = init_lexer("hello = 'helloworld'");
    lexer_collect_tokens(lexer);
    parser_T* parser = init_parser(lexer->token_list);
    parser_parse(parser);

    printf("%s", cast(ast_T*, parser->core_node->compound->values[0])->variable_definition->name);
    printf("%lu", cast(ast_T*, parser->core_node->compound->values[0])->variable_definition->value->string->size);


}