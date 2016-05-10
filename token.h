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

typedef int token_t;

const char* token_print(int token);

#endif // TOKEN__H_
