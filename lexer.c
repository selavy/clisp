#include "lexer.h"
#include <string.h>
#include <stdlib.h>

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
    in->end = in->stream + size;
    in->pos = in->stream;
    input = (void*)in;
    return true;
}

bool lexer_destroy(input_t *input) {
    if (!input)
        return true;
    struct _input_t *in = (struct _input_t*)input;
    free(in->stream);
    free(in);
    return true;
}

bool lexer_lex(input_t *input, token_t *token) {
    return false;
}
