#ifndef OBJECT__H_
#define OBJECT__H_

#include <stdint.h>

enum {
    OBJ_VOID,
    OBJ_NUMBER,
    OBJ_STRING,
    OBJ_IDENT,
    OBJ_EXPR,
    OBJ_FUNCTION,
    OBJ_CONS,
    OBJ_LIST
};

typedef unsigned char object_type_t;

typedef void* object_t;

struct string_t {
    object_type_t type;
    char *str;
    int64_t len;
};

struct number_t {
    object_type_t type;
    double val;
};

struct ident_t {
    object_type_t type;
    char *name;
    int64_t len;
};

struct expr_t {
    object_type_t type;
    object_t *terms;
    int64_t len;
};

object_t object_create_number(double val);
object_t object_create_string(const char *beg, const char *end);
object_t object_create_ident(const char *beg, const char *end);
object_t object_create_expr(object_t *terms, int64_t len);
int object_destroy(object_t object);
void object_debug_print(object_t obj);
const char *string_print(struct string_t *string);
const char *ident_print(struct ident_t *ident);

#define object_get_type(obj) (*(object_type_t*)obj)

#endif // OBJECT__H_
