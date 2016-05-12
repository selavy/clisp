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

typedef unsigned char token_type_t;
struct token_t {
    token_type_t type;
    const char* beg;
    const char* end;
};

const char* token_print(token_type_t token);

#endif // TOKEN__H_
