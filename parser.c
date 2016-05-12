#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "token.h"
#include "object.h"

#define STACK_SZ 100

enum {
    ST_INIT,
    ST_LIST,
    ST_ERR,
    ST_FIN
};

typedef unsigned char state_type_t;

struct state_t {
    state_type_t type;
    struct object_t *ast;
    struct object_t *stack[STACK_SZ];
    int pos;
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
    state->type = ST_INIT;
    state->ast = 0;
    state->pos = 0;
    memset(&state->stack[0], 0, sizeof(state->stack[0]) * STACK_SZ);
    *parser = (void*)state;
    return 0;
}

int parse_term(struct state_t *state, struct token_t *token) {
    switch (token->type) {
        case TK_NUMBER: {
            const int val = parse_int(token->beg, token->end);
            struct object_t *obj = malloc(sizeof(*obj));
            if (object_create_number(val, obj) != 0) {
                free(obj);
                return 1;
            }
            state->stack[state->pos++] = obj;
            return 0;
        }
        case TK_STRING:
            printf("String!\n");
            return 0;
        case TK_IDENT:
            printf("Ident!\n");
            return 0;
        default:
            state->type = ST_ERR;
            return 1;
    }
}

int parse_expr(struct state_t *state, struct token_t *token) {
    if (state->type == ST_ERR || state->type == ST_FIN) { // unnecessary?
        return 1;
    } else if (token->type == TK_EOF) {
        if (state->pos == 1) {
            state->type = ST_FIN;
            state->ast = state->stack[0];
            return 0;
        } else {
            state->type = ST_ERR;
            return 1;
        }
    } else if (state->type == ST_LIST) {
        return 0;
    } else if (token->type == TK_LPAREN) {
        state->type = ST_LIST;
        return 0;
    } else {
        return parse_term(state, token);
    }
}

int parser_parse(parser_t parser, struct token_t *token) {
    struct state_t *state = (struct state_t*)parser;
    return parse_expr(state, token);
}

int parser_get_ast(parser_t parser, ast_t *ast) {
    struct state_t *state = (struct state_t*)parser;
    if (state->type != ST_FIN) {
        *ast = 0;
        return 1;
    } else {
        *ast = state->ast; 
        return 0;
    }
}

int parser_destroy(parser_t *parser) {
    if (!*parser)
        return 0;
    struct state_t *state = (struct state_t*)*parser;
    free(state);
    *parser = 0;
    return 0;
}
