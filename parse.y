/* Process this file with `lemon parse.y` to create parse.h and parse.c */

/* All token codes are small integers with #defines that begin with "TK_" */
%token_prefix TK_

/* The type of the data attached to each token is Token.  This is also the */
/* default type for non-terminals. */
%token_type {token_t}
%default_type {token_t}

/* The following text is included near the beginning of the C source
 * code file that implements the parser.
*/
%include {

#include <assert.h>
#include "token.h"

/* Disable all error recovery processing in the parser push-down automaton. */
#define YYNOERRORRECOVERY 1

/* Indicate that parserFree() will never be called with a null pointer */
#define YYPARSEFREENEVERNULL 1

} /* end %include */

input ::= expr.
expr ::= LPAREN expr RPAREN.
expr ::= VALUE.
