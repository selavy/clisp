#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include "token.h"
#include "object.h"
#include "lexer.h"

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

struct _psr_t {
   lexer_t lexer; 
   struct token_t token;
};
int psr_init(parser_t *psr, const char *stream) {
    struct _psr_t *p = malloc(sizeof(*p));
    if (!p)
        return 1;
    if (lexer_init(&p->lexer, stream) != 0) {
        free(p);
        return 1;
    }
    *psr = p;
    return 0;
}

int psr_term(struct _psr_t *psr, struct object_t *obj) {
    int val;
    switch (psr->token.type) {
        case TK_NUMBER:
            val = parse_int(psr->token.beg, psr->token.end);
            if (object_create_number(val, obj) != 0) {
                return 1;
            }
            break;
        case TK_STRING:
            if (object_create_string(psr->token.beg, psr->token.end, obj) != 0) {
                return 1;
            }
            break;
        case TK_IDENT:
            assert(0); // TODO: implement
            break;
        default:
            assert(0); // TODO: error handling
            return 1;
    }
    printf("psr_term: "); object_debug_print(obj);
    return 0;
}

int psr_parse(parser_t psr, struct object_t *root) {
    struct _psr_t *p = (struct _psr_t*)psr;
    if (lexer_lex(p->lexer, &p->token) != 0) // prime first token
        return 1;
    if (psr_term(p, root) != 0)
        return 1;
    if (lexer_lex(p->lexer, &p->token) == 0) // stuff was left in the stream
        return 1;
    if (p->token.type != TK_EOF)
        return 1;
    printf("psr_parse: "); object_debug_print(root);
    return 0;
}

int psr_destroy(parser_t *psr) {
    if (!*psr)
        return 0;
    struct _psr_t *p = (struct _psr_t*)*psr;
    lexer_destroy(&p->lexer);
    free(p);
    *psr = 0;
    return 0;
}
