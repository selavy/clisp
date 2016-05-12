#ifndef LEXER__H_
#define LEXER__H_

#include "token.h"

typedef void* lexer_t;
int lexer_init(lexer_t *lexer, const char *stream);
int lexer_destroy(lexer_t *lexer);
int lexer_lex(lexer_t lexer, struct token_t *token);

#endif // LEXER__H_
