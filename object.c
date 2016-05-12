#include "object.h"
#include <stdint.h>

int object_create_number(double val, struct object_t *object) {
    object->type = OBJ_NUMBER;
    object->val = (int64_t)val;
    return 0;
}
