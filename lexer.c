#include "lexer.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

struct _lexer_t {
    char *stream;
    const char *pos;
    const char *end;
};

int lexer_init(lexer_t *lexer, const char *stream) {
    struct _lexer_t *lex = malloc(sizeof(*lex));
    const size_t size = strlen(stream);
    lex->stream = malloc(size * sizeof(char));
    strncpy(lex->stream, stream, size);
    lex->pos = lex->stream;
    lex->end = lex->pos + size;
    *lexer = (void*)lex;
    return 0;
}

int lexer_destroy(lexer_t *lexer) {
    if (!*lexer)
        return 0;
    struct _lexer_t *in = (struct _lexer_t*)*lexer;
    free(in->stream);
    free(in);
    *lexer = 0;
    return 0;
}

int lexer_lex(lexer_t lexer, struct token_t *token) {
    struct _lexer_t *in = (struct _lexer_t*)lexer;
    if (in->pos >= in->end) {
        token->type = TK_EOF;
        return 1;
    } else {
        while (in->pos < in->end && isspace(*in->pos)) {
            ++in->pos;
        }

        if (in->pos >= in->end) {
            return 1;
        } else if (*in->pos == '(') {
            token->type = TK_LPAREN;
            ++in->pos;
            return 0;
        } else if (*in->pos == ')') {
            token->type = TK_RPAREN;
            ++in->pos;
            return 0;
        } else if (isdigit(*in->pos)) {
            token->type = TK_NUMBER;
            token->beg = in->pos++;
            while (in->pos < in->end) {
                if (!isdigit(*in->pos) && *in->pos != '.') {
                    token->end = in->pos;
                    return 0;
                }
                ++in->pos;
            }
            token->end = in->pos;
            return 0;
        } else if (*in->pos == '"') {
            token->type = TK_STRING;
            token->beg = in->pos++;
            while (in->pos < in->end) {
                if (*in->pos == '"') {
                    token->end = ++in->pos;
                    return 0;
                }
                ++in->pos;
            }
            return 1;
        } else {
            token->type = TK_IDENT;
            token->beg = in->pos++;
            while (in->pos < in->end) {
                if (isspace(*in->pos) || *in->pos == '"') {
                    token->end = in->pos;
                    return 0;
                }
                ++in->pos;
            }
            return 1;
        }
    }
}
