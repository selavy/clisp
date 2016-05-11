/* Process this file with `lemon parse.y` to create parse.h and parse.c */

/* All token codes are small integers with #defines that begin with "TK_" */
%token_prefix TK_

/* The type of the data attached to each token is Token.  This is also the */
/* default type for non-terminals. */
%token_type {Token}
%default_type {Token}

/* The following text is included near the beginning of the C source
 * code file that implements the parser.
*/
%include {

/* The generated parser function takes a 4th argument as follows: */
%extra_argument {Parse *pParse}

/* Disable all error recovery processing in the parser push-down automaton. */
#define YYNOERRORRECOVERY 1

/* Indicate that parserFree() will never be called with a null pointer */
#define YYPARSEFREENEVERNULL 1

} /* end %include */

input ::= expr.
expr ::= LPAREN expr RPAREN.
expr ::= VALUE.
