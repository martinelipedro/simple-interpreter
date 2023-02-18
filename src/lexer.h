#ifndef LEXER_H
#define LEXER_H

typedef struct TOKEN_STRUCT
{
    enum
    {
        TOK_EOF = 0,
        TOK_ID, TOK_STRING, TOK_FLOAT, TOK_INTEGER

    } type;
    char* value;

} token_T;

token_T* init_token(int type, char* value);
char* token_get_repr_string(token_T* token);
void token_out(token_T* token);

typedef struct LEXER_STRUCT
{
    char* source;
    char current_char;
    unsigned int current_index;

} lexer_T;

lexer_T* init_lexer(char* source);
token_T* lexer_get_next_token(lexer_T* lexer);

#endif