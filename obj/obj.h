#ifndef MARK_SWEEP_GC_OBJ_H
#define MARK_SWEEP_GC_OBJ_H

#include "../vm/vm.h"

class VM;

enum class ObjectType;

class Object {
public:
    ObjectType type;
    unsigned char marked;

    /* The next object in the linked list of heap allocated objects. */
    struct Object *next;

    union {
        /* OBJ_INT */
        int value;

        /* OBJ_PAIR */
        struct {
            Object *head;
            Object *tail;
        };
    };

    void static objectPrint(Object *object);
};

#endif //MARK_SWEEP_GC_OBJ_H
