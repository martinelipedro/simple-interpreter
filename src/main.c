#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "lexer.h"
#include "casters.h"

int main()
{
    lexer_T* lexer = init_lexer("hello world");
    lexer_collect_tokens(lexer);

    token_out(as_token(dynamic_array_iterator_current(lexer->token_list)));
    dynamic_array_iterator_advance(lexer->token_list);
    token_out(as_token(dynamic_array_iterator_current(lexer->token_list)));
    token_out(as_token(dynamic_array_iterator_next(lexer->token_list)));
}