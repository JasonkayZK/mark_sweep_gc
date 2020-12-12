#ifndef MARK_SWEEP_GC_VM_H
#define MARK_SWEEP_GC_VM_H

#include "../obj/obj.h"

#define STACK_MAX 256
#define INIT_OBJ_NUM_MAX 8

class Object;

enum class ObjectType {
    OBJ_INT,
    OBJ_PAIR
};

class VM {
public:
    Object *stack[STACK_MAX]{};
    int stackSize;

    /* The first object in the linked list of all objects on the heap. */
    Object *firstObject;

    /* The total number of currently allocated objects. */
    int numObjects;

    /* The number of objects required to trigger a GC. */
    int maxObjects;

    VM();

    ~VM();

    void static assert(int condition, const char *message);

    void push(Object *value);

    Object *pop();

    void mark(Object *object);

    void markAll();

    void sweep();

    void gc();

    Object *newObject(ObjectType type);

    void pushInt(int intValue);

    Object *pushPair();

    void freeVM();
};

#endif //MARK_SWEEP_GC_VM_H
