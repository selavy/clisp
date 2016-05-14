#include "object.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

object_t object_create_number(double val) {
    //DEBUG
    printf("object_create_number\n");
    //GUBED
    struct number_t *number = malloc(sizeof(*number));
    if (!number)
        return 0;
    number->type = OBJ_NUMBER;
    number->val = val;
    return number;
}

// TODO: remove double quotes around string
object_t object_create_string(const char *beg, const char *end) {
    //DEBUG
    printf("object_create_string\n");
    //GUBED
    assert(beg <= end);
    struct string_t *str = malloc(sizeof(*str));
    if (str) {
        str->len = end - beg;
        if (str->len > 0) {
            str->str = malloc(str->len + 1);
            memcpy(&str->str[0], beg, str->len);
            str->str[str->len] = 0;
        } else {
            str = 0;
        }
        str->type = OBJ_STRING;
    }
    return str;
}

object_t object_create_ident(const char *beg, const char *end) {
    //DEBUG
    printf("object_create_ident\n");
    //GUBED
    assert(beg <= end);
    struct ident_t *ident = malloc(sizeof(*ident));
    if (ident) { 
        ident->len = end - beg;
        if (ident->len > 0) {
            ident->name = malloc(ident->len + 1);
            memcpy(&ident->name[0], beg, ident->len);
            ident->name[ident->len] = 0;
        } else {
            ident->name = 0;
        }
        ident->type = OBJ_IDENT;
    }
    return ident;
}

const char *string_print(struct string_t *s) {
    assert(s);
    assert(s->len >= 0);
    if (s->len == 0)
        return "";
    else
        return s->str;
}

const char *ident_print(struct ident_t *ident) {
    assert(ident);
    assert(ident->len >= 0);
    if (ident->len == 0)
        return "";
    else
        return ident->name;
}

void object_string_destroy(struct string_t *str) {
    if (str->len > 0) {
        free(str->str);
    }
    free(str);
}

void object_number_destroy(struct number_t *num) {
    free(num);
}

int object_destroy(object_t obj) {
    const object_type_t type = *(object_type_t*)obj;
    switch (type) {
        case OBJ_VOID:
            break;
        case OBJ_NUMBER:
            object_number_destroy(obj);
            break;
        case OBJ_STRING:
            object_string_destroy(obj);
            break;
        case OBJ_FUNCTION:
            assert(0);
            break;
        case OBJ_CONS:
            assert(0);
            break;
        case OBJ_LIST:
            assert(0);
            break;
        default:
            assert(0);
            break;
    }
    return 0;
}

void object_debug_print(object_t obj) {
    if (!obj) {
        printf("NULL\n");
    }
    switch (object_get_type(obj)) {
        case OBJ_VOID:
            printf("VOID\n");
            break;
        case OBJ_NUMBER:
            printf("NUMBER(%f)\n", ((struct number_t*)obj)->val);
            break;
        case OBJ_STRING:
            printf("STRING(%s)\n", string_print(obj));
            break;
        case OBJ_IDENT:
            printf("IDENT(%s)\n", ident_print(obj));
            break;
        default:
            //assert(0);
            printf("UNKNOWN TYPE(%d)\n", object_get_type(obj));
    }
}
