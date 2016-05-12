#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "token.h"
#include "object.h"

struct state_t {
};

int64_t parse_int(const char *beg, const char *end) {
    const char* p = end - 1;
    int64_t ret = 0;
    int64_t mult = 1;
    for (; p >= beg; --p) {
        ret += (*p - '0') * mult;
        mult *= 10;
    }
    return ret;
}

int parser_init(parser_t *parser) {
    struct state_t *state = malloc(sizeof(*state));
    *parser = (void*)state;
    return 0;
}

int parse_term(struct state_t *state, struct token_t *token) {
    switch (token->type) {
        case TK_NUMBER:
            printf("Number!\n");
            printf("Number = %llu\n", parse_int(token->beg, token->end));
            return 0;
        case TK_STRING:
            printf("String!\n");
            return 0;
        case TK_IDENT:
            printf("Ident!\n");
            return 0;
        default:
            return 1;
    }
}

int parse_expr(struct state_t *state, struct token_t *token) {
    return parse_term(state, token);
}

int parser_parse(parser_t parser, struct token_t *token) {
    struct state_t *state = (struct state_t*)parser;
    return parse_expr(state, token);
}

int parser_destroy(parser_t *parser) {
    if (!*parser)
        return 0;
    struct state_t *state = (struct state_t*)*parser;
    free(state);
    *parser = 0;
    return 0;
}
