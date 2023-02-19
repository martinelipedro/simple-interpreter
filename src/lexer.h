#ifndef LEXER_H
#define LEXER_H

#include "dynamic_array.h"

typedef struct TOKEN_STRUCT
{
    enum
    {
        TOK_EOF = 0,
        TOK_SEMI, TOK_COMMA,

        TOK_LPAREN, TOK_RPAREN,

        TOK_ID, TOK_STRING, TOK_FLOAT, TOK_INTEGER,


        TOK_EQUALS,

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
    dynamic_array_T* token_list;

} lexer_T;

lexer_T* init_lexer(char* source);
token_T* lexer_get_next_token(lexer_T* lexer);


void lexer_collect_tokens(lexer_T* lexer);
void lexer_collect_id(lexer_T* lexer);
void lexer_collect_string(lexer_T* lexer);
void lexer_make_end(lexer_T* lexer);


void lexer_advance(lexer_T* lexer);


#endif