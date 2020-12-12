#include "obj.h"
#include <iostream>

void objectPrint(Object *object) {
    switch (object->type) {
        case ObjectType::OBJ_INT:
            printf("%d", object->value);
            break;

        case ObjectType::OBJ_PAIR:
            printf("(");
            objectPrint(object->head);
            printf(", ");
            objectPrint(object->tail);
            printf(")");
            break;
    }
}
