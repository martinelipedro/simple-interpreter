#ifndef RUN_H
#define RUN_H

#include "parser.h"
#include "visitor.h"
#include "file_reader.h"
#include "casters.h"

void run(int argc, char** argv)
{
    if (argc < 2)
    {
        printf("Missing argument: [filepath]\n");
        exit(1);
    }

    lexer_T* lexer = init_lexer(get_file_contents(argv[1]));
    lexer_collect_tokens(lexer);
    parser_T* parser = init_parser(lexer->token_list);
    parser_parse(parser);


    printf("%s", cast(ast_T*, parser->core_node->compound->values[0])->binary_expr->rhs->binary_expr->lhs->literal_number->str);


    // visitor_T* visitor = init_visitor();
    // visitor_visit(visitor, parser->core_node); 
}

#endif