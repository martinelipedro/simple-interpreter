#include "token.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


token_T* init_token(int type, char* value)
{
    token_T* token = calloc(1, sizeof(struct TOKEN_STRUCT));
    token->type = type;
    token->value = value;

    return token;
}

char* token_get_repr_string(token_T* token)
{
    char* buffer = calloc(1, sizeof(char));
    size_t token_value_size = strlen(token->value);
    size_t token_other_size = strlen("(  :  )");
    size_t token_type_size = strlen("xx");
    
    buffer = realloc(buffer, (token_value_size, token_other_size, token_type_size + 1) * sizeof(char));
    sprintf(buffer, "( %d : %s )", token->type, token->value);

    return buffer;
}

void token_out(token_T* token)
{
    printf("%s", token_get_repr_string(token));
}