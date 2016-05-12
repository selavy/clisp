#include "token.h"

const char* token_print(token_type_t token) {
    switch (token) {
    case TK_IDENT:
        return "IDENT";
    case TK_NUMBER:
        return "NUMBER";
    case TK_STRING:
        return "STRING";
    case TK_LPAREN:
        return "LPAREN";
    case TK_RPAREN:
        return "TK_RPAREN";
    case TK_EOF:
        return "EOF";
    case TK_QUOTE:
        return "QUOTE";
    default:
        return "UNKNOWN";
    }
}
