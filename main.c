#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "token.h"
#include "lexer.h"

#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))
#define PRINTL(x, size) \
    do { \
        for (int i = 0; i < size; ++i) { \
            printf("%s\n", token_print(x[i])); \
        } \
    } while(0)

void check_case(const char *stream, const int *expected, int size) {
    int tokens[100];
    int pos = 0;
    input_t input;
    token_t token;
    int i;
    assert(lexer_init(&input, stream) == true);
    while (lexer_lex(input, &token)) {
        tokens[pos++] = token;
    }
    assert(lexer_destroy(&input) == true);
    assert(token == TK_EOF);
    /*
    printf("Pos = %d, size = %d\n", pos, size);
    PRINTL(tokens, pos);
    */
    assert(pos == size);
    for (i = 0; i < size; ++i) {
        assert(tokens[i] == expected[i]);
    }
}

int main(int argc, char **argv) {
    {
        const int expected[] = {
            TK_LPAREN,
            TK_IDENT,
            TK_STRING,
            TK_RPAREN
        };
        check_case("(print \"Hello\")", &expected[0], NELEMS(expected));
        printf("Passed Case 1\n");
    }
    {
        const int expected[] = {
            TK_LPAREN,
            TK_IDENT,
            TK_NUMBER,
            TK_NUMBER,
            TK_RPAREN
        };
        check_case("(+ 1 2)", &expected[0], NELEMS(expected));
        printf("Passed Case 2\n");
    }
    {
        const int expected[] = {
            TK_LPAREN,
            TK_IDENT,
            TK_NUMBER,
            TK_LPAREN,
            TK_IDENT,
            TK_NUMBER,
            TK_NUMBER,
            TK_RPAREN,
            TK_NUMBER,
            TK_RPAREN
        };
        check_case("(+ 1 (+ 2 3) 4)", &expected[0], NELEMS(expected));
        printf("Passed Case 3\n");
    }

    printf("Passed\n");
    return 0;
}
