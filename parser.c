#include "parser.h"
#include "token.h"
#include <stdlib.h>

struct state_t {
};

int parser_init(parser_t *parser) {
    struct state_t *state = malloc(sizeof(*state));
    *parser = (void*)state;
    return 0;
}

int parser_parse(parser_t parser, struct token_t *token) {
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
