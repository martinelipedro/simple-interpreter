#ifndef LEXER_H
#define LEXER_H

#include "dynamic_array.h"
#include "token.h"

typedef struct LEXER_STRUCT
{
    char* source;
    char current_char;
    unsigned int current_index;
    dynamic_array_T* token_list;

} lexer_T;

lexer_T* init_lexer(char* source);

void lexer_collect_tokens(lexer_T* lexer);
void lexer_collect_id(lexer_T* lexer);
void lexer_collect_string(lexer_T* lexer);
void lexer_collect_number(lexer_T* lexer);
void lexer_make_end(lexer_T* lexer);


void lexer_advance(lexer_T* lexer);


#endif