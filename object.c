#include "object.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct string_t {
    char *str;
    size_t len;
};
struct cons_t {
    struct object_t *car;
    struct object_t *cdr;
};

int object_create_number(double val, struct object_t *object) {
    /* printf("OBJECT creating number with value: %f\n", val); */ 
    object->type = OBJ_NUMBER;
    object->val = val;
    return 0;
}

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

int
object_create_cons(struct object_t *car, struct object_t *cdr, struct object_t *object) {
    assert(car != 0); // required?
    struct cons_t *cons = malloc(sizeof(*cons));
    if (!cons)
        return 1;
    cons->car = car;
    cons->cdr = cdr;
    object->type = OBJ_CONS; 
    object->ptr = cons;
    return 0;
}

void object_string_destroy(struct object_t *obj) {
    struct string_t *str = (struct string_t*)obj->ptr;
    if (str->len > 0) {
        free(str->str);
    }
    free(str);
    obj->ptr = 0;
    free(obj);
}

void object_cons_destroy(struct object_t *obj) {
    struct cons_t *cons = (struct cons_t*)obj->ptr;
    if (cons->car) {
        object_destroy(&(cons->car));
        cons->car = 0;
    }
    if (cons->cdr) {
        object_destroy(&(cons->cdr));
        cons->cdr = 0;
    }
    free(cons);
    obj->ptr = 0;
    free(obj);
}

int object_destroy(struct object_t **object) {
    if (!*object)
        return 0;
    struct object_t *obj = *object;
    switch (obj->type) {
        case OBJ_VOID:
            break;
        case OBJ_NUMBER:
            free(obj);
            *object = 0;
            break;
        case OBJ_STRING:
            object_string_destroy(obj);
            *object = 0;
            break;
        case OBJ_FUNCTION:
            break;
        case OBJ_CONS:
            object_cons_destroy(obj);
            *object = 0;
            break;
        case OBJ_LIST:
            break;
        default:
            assert(0);
            break;
    }
    return 0;
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
