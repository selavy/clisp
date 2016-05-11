#ifndef TOKEN__H_
#define TOKEN__H_

enum {
    TOKEN_IDENT = 0,
    TOKEN_NUMBER,
    TOKEN_STRING,
    TOKEN_OPEN_PAREN,
    TOKEN_CLOSE_PAREN,
    TOKEN_EOF
};

typedef unsigned char token_t;

const char* token_print(token_t token);

#endif // TOKEN__H_
