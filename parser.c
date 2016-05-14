#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include "token.h"
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
int parser_init(parser_t *psr, const char *stream) {
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

int parse_term(struct _psr_t *psr, object_t *obj) {
    int val;
    switch (psr->token.type) {
        case TK_NUMBER:
            val = parse_int(psr->token.beg, psr->token.end);
            *obj = object_create_number(val);
            if (!*obj) return 1;
            break;
        case TK_STRING:
            *obj = object_create_string(psr->token.beg, psr->token.end);
            if (!*obj) return 1;
            break;
        case TK_IDENT:
            *obj = object_create_ident(psr->token.beg, psr->token.end);
            if (!*obj) return 1;
            break;
        default:
            assert(0); // TODO: error handling
            return 1;
    }
    printf("parse_term: "); object_debug_print(*obj);
    return 0;
}

#define token_type(psr) (psr).token.type

int parse_expr(struct _psr_t *psr, object_t *obj) {
    if (psr->token.type == TK_LPAREN) {
        object_t terms[100];
        int pos = 0;
        while (lexer_lex(psr->lexer, &psr->token) == 0 && token_type(*psr) != TK_RPAREN) {
            object_t tmp;
            if (parse_expr(psr, &tmp) != 0)
                return 1;
            terms[pos++] = tmp;
        }
        if (token_type(*psr) != TK_RPAREN) {
            for (int i = 0; i < pos; ++i) free(terms[i]);
            return 1;
        }
        *obj = object_create_expr(&terms[0], pos);
        if (!*obj)
            return 1;
        return 0;
    } else {
        return parse_term(psr, obj);
    }
}

int parser_parse(parser_t psr, object_t *root) {
    struct _psr_t *p = (struct _psr_t*)psr;
    if (lexer_lex(p->lexer, &p->token) != 0) // prime first token
        return 1;
    if (parse_expr(p, root) != 0)
        return 1;
    if (lexer_lex(p->lexer, &p->token) == 0) // stuff was left in the stream
        return 1;
    if (p->token.type != TK_EOF)
        return 1;
    printf("psr_parse: "); object_debug_print(*root);
    return 0;
}

int parser_destroy(parser_t *psr) {
    if (!*psr)
        return 0;
    struct _psr_t *p = (struct _psr_t*)*psr;
    lexer_destroy(&p->lexer);
    free(p);
    *psr = 0;
    return 0;
}
