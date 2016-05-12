#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include "token.h"
#include "object.h"

struct state_t {
};

int parser_init(parser_t *parser) {
    struct state_t *state = malloc(sizeof(*state));
    *parser = (void*)state;
    return 0;
}

int parser_parse(parser_t parser, struct token_t *token) {
    //struct state_t *state = (struct state_t*)*parser;
    switch (token->type) {
        case TK_NUMBER:
            printf("NUMBER(%.*s)\n", (int)(token->end - token->beg), token->beg);
            break;
        case TK_STRING:
            printf("STRING(%.*s)\n", (int)(token->end - token->beg), token->beg);
            break;
        case TK_IDENT:
            printf("IDENT(%.*s)\n", (int)(token->end - token->beg), token->beg);
            break;
        case TK_LPAREN:
            printf("LPAREN\n");
            break;
        case TK_RPAREN:
            printf("RPAREN\n");
            break;
        case TK_EOF:
            printf("EOF\n");
            break;
    }

    return 0;
}

int parser_destroy(parser_t *parser) {
    if (!*parser)
        return 0;
    struct state_t *state = (struct state_t*)*parser;
    free(state);
    *parser = 0;
    return 0;
}
