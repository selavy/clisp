#include "object.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int object_create_number(double val, struct object_t *object) {
    printf("OBJECT creating number with value: %f\n", val);
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

const char* print_string(struct string_t *s) {
    assert(s);
    assert(s->len >= 0);
    if (s->len == 0) {
        return "";
    } else {
        return s->str;
    }
}

void object_debug_print(struct object_t *obj) {
    if (!obj) {
        printf("NULL OBJECT\n");
    } else {
        switch (obj->type) {
            case OBJ_VOID:
                printf("VOID\n");
                break;
            case OBJ_NUMBER:
                printf("Number(%f)\n", obj->val);
                break;
            case OBJ_STRING:
                printf("String(%s)\n", print_string((struct string_t*)obj->ptr));
                break;
            default:
                printf("UNKNOWN\n");
                break;
        }
    }
}
