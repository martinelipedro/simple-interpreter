#include "lexer.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

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

lexer_T* init_lexer(char* source)
{
    lexer_T* lexer = calloc(1, sizeof(struct LEXER_STRUCT));

    lexer->source = source;
    lexer->current_char = source[0];
    lexer->current_index = 0;
    lexer->token_list = init_dynamic_array(sizeof(struct TOKEN_STRUCT));

    return lexer;
}

void lexer_collect_tokens(lexer_T* lexer)
{
    while (lexer->current_char)
    {
        if (isalpha(lexer->current_char))
        {
            lexer_collect_id(lexer);
        }
        else if (isdigit(lexer->current_char))
        {
            lexer_collect_number(lexer);
        }

        switch (lexer->current_char)
        {
            case ' ':
            case '\n':
            case '\r': lexer_advance(lexer); break;
            case '\'': lexer_collect_string(lexer); break;

    
            case '=': dynamic_array_push(lexer->token_list, (void*)init_token(TOK_EQUALS, "=")); lexer_advance(lexer); break;
            case ';': dynamic_array_push(lexer->token_list, (void*)init_token(TOK_SEMI, ";")); lexer_advance(lexer); break;
            case '(': dynamic_array_push(lexer->token_list, (void*)init_token(TOK_LPAREN, "(")); lexer_advance(lexer); break;
            case ')': dynamic_array_push(lexer->token_list, (void*)init_token(TOK_RPAREN, ")"));lexer_advance(lexer); break;
            case ',': dynamic_array_push(lexer->token_list, (void*)init_token(TOK_COMMA, ","));lexer_advance(lexer); break;

        }
    }
    lexer_make_end(lexer);
}


/* I know, horrible solution to generate more than one EOF and not worry about the end checking in the parser. */
/* */
void lexer_make_end(lexer_T* lexer)
{
    for (size_t i = 0; i < 2; i++)
    {
        dynamic_array_push(lexer->token_list, (void*)init_token(TOK_EOF, "(null)"));
    }
}

void lexer_collect_id(lexer_T* lexer)
{
    char* buffer = calloc(1, sizeof(char));

    while (isalpha(lexer->current_char))
    {
        buffer = realloc(buffer, (strlen(buffer) + 2) * sizeof(char));
        strcat(buffer, (char[]){lexer->current_char, 0});
        lexer_advance(lexer);
    }

    dynamic_array_push(lexer->token_list, (void*)init_token(TOK_ID, buffer));
}

void lexer_collect_string(lexer_T* lexer)
{
    char* buffer = calloc(1, sizeof(char));

    lexer_advance(lexer);

    while (lexer->current_char != '\'')
    {
        buffer = realloc(buffer, (strlen(buffer) + 2) * sizeof(char));
        strcat(buffer, (char[]){lexer->current_char, 0});
        lexer_advance(lexer);
    }

    lexer_advance(lexer);

    dynamic_array_push(lexer->token_list, (void*)init_token(TOK_STRING, buffer));
}

void lexer_collect_number(lexer_T* lexer)
{
    char* buffer = calloc(1, sizeof(char));
    int dot_count = 0;

    while (isdigit(lexer->current_char) || lexer->current_char == '.')
    {
        if (dot_count > 2)
        {
            printf("Two dots in a single number!");
            exit(1);
        }
        
        if (lexer->current_char == '.')
        {
            dot_count++;
        }
        

        buffer = realloc(buffer, (strlen(buffer) + 2) * sizeof(char));
        strcat(buffer, (char[]){lexer->current_char, 0});
        lexer_advance(lexer);
    }

    dynamic_array_push(lexer->token_list, (void*)init_token(TOK_NUMBER, buffer));
}

void lexer_advance(lexer_T* lexer)
{
    if (lexer->current_char)
    {
        lexer->current_index += 1;
        lexer->current_char = lexer->source[lexer->current_index];
    }
}