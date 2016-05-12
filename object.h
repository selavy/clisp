#ifndef OBJECT__H_
#define OBJECT__H_

enum {
    OBJ_VOID,
    OBJ_NUMBER,
    OBJ_STRING,
    OBJ_FUNCTION,
    OBJ_LIST
};

typedef unsigned char object_type_t;

struct object_t {
    object_type_t type;
    void *data;
};

#endif // OBJECT__H_
