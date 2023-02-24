#ifndef TOKEN_H
#define TOKEN_C

typedef struct TOKEN_STRUCT
{
    enum
    {
        TOK_EOF = 0,
        TOK_SEMI, TOK_COMMA,

        TOK_LPAREN, TOK_RPAREN,

        TOK_ID, TOK_STRING, TOK_NUMBER,

        TOK_PLUS, TOK_MINUS, TOK_STAR, TOK_SLASH,


        TOK_EQUALS,

    } type;
    char* value;

} token_T;

token_T* init_token(int type, char* value);
char* token_get_repr_string(token_T* token);
void token_out(token_T* token);

#endif