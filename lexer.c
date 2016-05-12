#include "lexer.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

struct _input_t {
    char *stream;
    const char *pos;
    const char *end;
};

bool lexer_init(lexer_t *lexer, const char *stream) {
    struct _input_t *in = malloc(sizeof(*in));
    const size_t size = strlen(stream);
    in->stream = malloc(size * sizeof(char));
    strncpy(in->stream, stream, size);
    in->pos = in->stream;
    in->end = in->pos + size;
    *lexer = (void*)in;

    return true;
}

bool lexer_destroy(lexer_t *lexer) {
    if (!*lexer)
        return true;
    struct _input_t *in = (struct _input_t*)*lexer;
    free(in->stream);
    free(in);
    *lexer = 0;
    return true;
}

bool lexer_lex(lexer_t lexer, struct token_t *token) {
    struct _input_t *in = (struct _input_t*)lexer;
    if (in->pos >= in->end) {
        token->type = TK_EOF;
        return false;
    } else {
        while (in->pos < in->end && isspace(*in->pos)) {
            ++in->pos;
        }

        if (in->pos >= in->end) {
            return false;
        } else if (*in->pos == '(') {
            token->type = TK_LPAREN;
            ++in->pos;
            return true;
        } else if (*in->pos == ')') {
            token->type = TK_RPAREN;
            ++in->pos;
            return true;
        } else if (isdigit(*in->pos)) {
            token->type = TK_NUMBER;
            ++in->pos;
            while (in->pos < in->end) {
                if (!isdigit(*in->pos) && *in->pos != '.') {
                    return true;
                }
                ++in->pos;
            }
            return false;
        } else if (*in->pos == '"') {
            token->type = TK_STRING;
            ++in->pos;
            while (in->pos < in->end) {
                if (*in->pos == '"') {
                    ++in->pos;
                    return true;
                }
                ++in->pos;
            }
            return false;
        } else {
            token->type = TK_IDENT;
            ++in->pos;
            while (in->pos < in->end) {
                if (isspace(*in->pos) || *in->pos == '"') {
                    return true;
                }
                ++in->pos;
            }
            return false;
        }
    }
}
