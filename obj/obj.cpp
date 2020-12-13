#include "obj.h"
#include <iostream>

void Object::objectPrint(Object *object) {
    switch (object->type) {
        case ObjectType::OBJ_INT:
            std::cout << object->value << std::endl;
            break;

        case ObjectType::OBJ_PAIR:
            printf("(");
            Object::objectPrint(object->head);
            printf(", ");
            Object::objectPrint(object->tail);
            printf(")");
            break;
    }
}
