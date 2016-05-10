#include <stdio.h>
#include <stdlib.h>
#include "token.h"
#include "lexer.h"

int main(int argc, char **argv) {
    const char *stream = "( 1 + 2 )";

    printf("stream: '%s'\n", stream);

    input_t input = 0;
    if (!lexer_init(&input, stream)) {
        perror("lexer_init");
        exit(1);
    }

    token_t token;
    while (lexer_lex(input, &token)) {
        puts(token_print(token));
    }

    if (!lexer_destroy(&input)) {
        perror("lexer_destroy");
        exit(1);
    }

    return 0;
}
