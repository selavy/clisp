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

bool lexer_init(input_t *input, const char *stream) {
    struct _input_t *in = malloc(sizeof(*in));
    const size_t size = strlen(stream);
    in->stream = malloc(size * sizeof(char));
    strncpy(in->stream, stream, size);
    in->pos = in->stream;
    in->end = in->pos + size;
    *input = (void*)in;

    return true;
}

bool lexer_destroy(input_t *input) {
    if (!*input)
        return true;
    struct _input_t *in = (struct _input_t*)*input;
    free(in->stream);
    free(in);
    *input = 0;
    return true;
}

bool lexer_lex(input_t input, token_t *token) {
    struct _input_t *in = (struct _input_t*)input;
    if (in->pos >= in->end) {
        printf("END DETECTED\n");
        *token = TOKEN_EOF;
        return false;
    } else {
        while (in->pos < in->end && isspace(*in->pos)) {
            ++in->pos;
        }

        if (in->pos >= in->end) {
            printf("unexpected end!\n");
            return false;
        } else if (*in->pos == '(') {
            *token = TOKEN_OPEN_PAREN;
            ++in->pos;
            return true;
        } else if (*in->pos == ')') {
            *token =  TOKEN_CLOSE_PAREN;
            ++in->pos;
            return true;
        } else if (isdigit(*in->pos)) {
            *token = TOKEN_NUMBER;
            while ((isdigit(*in->pos) || *in->pos == '.') && in->pos < in->end) {
                ++in->pos;
            }
            if (in->pos >= in->end) {
                return false;
            }
            return true;
        } else if (*in->pos == '"') {
            ++in->pos;
            *token = TOKEN_STRING;
            while (in->pos < in->end && *in->pos != '"') {
                ++in->pos;
            }
            if (*in->pos == '"') {
                ++in->pos;
                return true;
            } else {
                return false;
            }
        } else {
            *token = TOKEN_IDENT;
            ++in->pos;
            while (in->pos < in->end) {
                ++in->pos;
                if (isspace(*in->pos) || *in->pos == '"') {
                    return true;
                }
            }
            return false;
        }
    }
}
