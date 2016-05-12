#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "token.h"
#include "lexer.h"
#include "parser.h"

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
    lexer_t lexer;
    struct token_t token;
    int i;
    assert(lexer_init(&lexer, stream) == 0);
    while (lexer_lex(lexer, &token) == 0) {
        tokens[pos++] = token.type;
    }
    assert(lexer_destroy(&lexer) == 0);
    assert(token.type == TK_EOF);
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
    {
        const int expected[] = { TK_NUMBER };
        check_case("123", &expected[0], NELEMS(expected));
        printf("Passed Case 4\n");
    }
    {
        const int expected[] = { TK_STRING };
        check_case("\"Hello World\"", &expected[0], NELEMS(expected));
        printf("Passed Case 5\n");
    }

    const char *stream = "123";
    lexer_t lexer;
    parser_t parser;
    assert(lexer_init(&lexer, stream) == 0);
    assert(parser_init(&parser) == 0);

    struct token_t token;
    while (lexer_lex(lexer, &token) == 0) {
        printf("Token: %s\n", token_print(token.type));
        assert(parser_parse(parser, &token) == 0);
    }

    assert(token.type = TK_EOF);
    assert(lexer_destroy(&lexer) == 0);
    assert(parser_destroy(&parser) == 0);
    printf("Passed Case 6\n");

    printf("Passed\n");
    return 0;
}
