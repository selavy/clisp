#ifndef LEXER__H_
#define LEXER__H_

#include "token.h"
#include <stdbool.h>

typedef void input_t;

bool lexer_init(input_t *input, const char *stream);
bool lexer_destroy(input_t *input);
bool lexer_lex(input_t *input, token_t *token);

#endif // LEXER__H_
