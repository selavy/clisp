#ifndef OBJECT__H_
#define OBJECT__H_

#include <stdint.h>

enum {
    OBJ_VOID,
    OBJ_NUMBER,
    OBJ_STRING,
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

object_t object_create_number(double val);
object_t object_create_string(const char *beg, const char *end);
int object_destroy(object_t object);
void object_debug_print(object_t obj);

#define object_get_type(obj) (*(object_type_t*)obj)

#endif // OBJECT__H_
