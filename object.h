#ifndef OBJECT__H_
#define OBJECT__H_

enum {
    OBJ_VOID,
    OBJ_NUMBER,
    OBJ_STRING,
    OBJ_FUNCTION,
    OBJ_CONS,
    OBJ_LIST
};

typedef unsigned char object_type_t;

struct object_t {
    object_type_t type;
    union {
        void *ptr;
        double val;

    };
};

int object_create_number(double val, struct object_t *object);
int object_create_string(const char *beg, const char *end, struct object_t *object);
int object_create_cons(struct object_t *car, struct object_t *cdr, struct object_t *object);
int object_destroy(struct object_t **object);
void object_debug_print(struct object_t *obj);

#endif // OBJECT__H_