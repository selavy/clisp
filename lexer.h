#ifndef LEXER__H_
#define LEXER__H_

#include "token.h"
#include <stdbool.h>

typedef void* lexer_t;
bool lexer_init(lexer_t *lexer, const char *stream);
bool lexer_destroy(lexer_t *lexer);
bool lexer_lex(lexer_t lexer, struct token_t *token);

#endif // LEXER__H_
