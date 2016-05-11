#ifndef TOKEN__H_
#define TOKEN__H_

enum {
    TK_IDENT,
    TK_NUMBER,
    TK_STRING,
    TK_LPAREN,
    TK_RPAREN,
    TK_EOF
};

typedef unsigned char token_t;

const char* token_print(token_t token);

#endif // TOKEN__H_
