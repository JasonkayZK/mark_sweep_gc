#ifndef MARK_SWEEP_GC_VM_H
#define MARK_SWEEP_GC_VM_H

#include "../obj/obj.h"

#define STACK_MAX 256
#define INIT_OBJ_NUM_MAX 8

struct Object;

enum class ObjectType {
    OBJ_INT,
    OBJ_PAIR
};

struct VM {
    Object *stack[STACK_MAX];
    int stackSize;

    /* The first object in the linked list of all objects on the heap. */
    Object *firstObject;

    /* The total number of currently allocated objects. */
    int numObjects;

    /* The number of objects required to trigger a GC. */
    int maxObjects;
};

void assert(int condition, const char *message);

VM *newVM();

void push(VM *vm, Object *value);

Object *pop(VM *vm);

void mark(Object *object);

void markAll(VM *vm);

void sweep(VM *vm);

void gc(VM *vm);

Object *newObject(VM *vm, ObjectType type);

void pushInt(VM *vm, int intValue);

Object *pushPair(VM *vm);


void freeVM(VM *vm);

#endif //MARK_SWEEP_GC_VM_H
