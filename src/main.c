#include "parser.h"
#include "casters.h"
#include "map.h"

#include <stdio.h>

int main()

{
    // lexer_T* lexer = init_lexer("print('hello');");
    // lexer_collect_tokens(lexer);
    // parser_T* parser = init_parser(lexer->token_list);
    // parser_parse(parser);

    // printf("%s", cast(ast_T*, cast(ast_T*, parser->core_node->compound->values[0])->funcion_call->arguments->compound->values[0])->string->value);

    map_T* map = init_map(sizeof(int));
    map_add(map, "test", (void*)54);
    printf("%d\n", map_has_key(map, "test"));
    printf("%d\n", map_has_key(map, "asd"));
}