#ifndef PARSER__H_
#define PARSER__H_

struct token_t;
typedef void* parser_t;
typedef void* ast_t;
struct object_t;

int parser_init(parser_t *parser);
int parser_parse(parser_t parser, struct token_t *token);
int parser_get_ast(parser_t parser, ast_t *ast);
int parser_destroy(parser_t *parser);

typedef void* psr_t;
int psr_init(psr_t *psr, const char *stream);
int psr_parse(psr_t psr, struct object_t *root);
int psr_destroy(psr_t *psr);

#endif // PARSER__H_
