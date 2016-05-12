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
// TODO: optimize by switching `beg` and `end` to int and
// storing indices into stream?  sizeof(char*) == 2*sizeof(int)
// 
// maybe best to do
//struct token_t {
//    int64_t type; //  8 bytes
//    int beg;      //  4 bytes
//    int end;      //  4 bytes
//                  //  -------
//                  // 16 bytes
//};
struct token_t {
    token_type_t type; // 1 byte
    const char* beg;   // 8 bytes
    const char* end;   // 8 bytes
                       // -------
                       // 9 bytes
    //char padding[7]; // ???
};

const char* token_print(token_type_t token);

#endif // TOKEN__H_
