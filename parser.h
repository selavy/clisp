#ifndef PARSER__H_
#define PARSER__H_

struct token_t;
typedef void* parser_t;


int parser_init(parser_t *parser);
int parser_parse(parser_t parser, struct token_t *token);
int parser_destroy(parser_t *parser);

#endif // PARSER__H_
