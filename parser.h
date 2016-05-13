#ifndef PARSER__H_
#define PARSER__H_

#include "object.h"

struct token_t;  // fwd

typedef void* parser_t;

int psr_init(parser_t *parser, const char *stream);
int psr_parse(parser_t parser, object_t *root);
int psr_destroy(parser_t *parser);

#endif // PARSER__H_
