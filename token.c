#include "token.h"

const char* token_print(token_t token) {
    switch (token) {
    case TOKEN_IDENT:
        return "IDENT";
    case TOKEN_NUMBER:
        return "NUMBER";
    case TOKEN_STRING:
        return "STRING";
    case TOKEN_OPEN_PAREN:
        return "OPEN_PAREN";
    case TOKEN_CLOSE_PAREN:
        return "CLOSE_PAREN";
    case TOKEN_EOF:
        return "EOF";
    default:
        return "UNKNOWN";
    }
}
