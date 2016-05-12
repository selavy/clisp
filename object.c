#include "object.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int object_create_number(double val, struct object_t *object) {
    object->type = OBJ_NUMBER;
    object->val = val;
    return 0;
}

struct string_t {
    char *str;
    size_t len;
};
int object_create_string(const char* beg, const char *end, struct object_t *object) {
    assert(beg <= end);
    struct string_t *s = malloc(sizeof(*s));
    if (!s)
        return 1;

    s->len = end - beg;
    if (s->len > 0) {
        s->str = malloc(s->len + 1);
        memcpy(&s->str[0], beg, s->len);
        s->str[s->len] = 0;
    } else {
        s = 0;
    }
    object->type = OBJ_STRING;
    object->ptr = s;
    return 0;
}
