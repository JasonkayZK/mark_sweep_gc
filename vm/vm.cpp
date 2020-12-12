#include "vm.h"
#include <iostream>
#include <cstdlib>

void assert(int condition, const char *message) {
    if (!condition) {
        printf("%s\n", message);
        exit(1);
    }
}

VM *newVM() {
    VM *vm = static_cast<VM *>(malloc(sizeof(VM)));
    vm->stackSize = 0;
    vm->firstObject = nullptr;
    vm->numObjects = 0;
    vm->maxObjects = INIT_OBJ_NUM_MAX;
    return vm;
}


void push(VM *vm, Object *value) {
    assert(vm->stackSize < STACK_MAX, "Stack overflow!");
    vm->stack[vm->stackSize++] = value;
}


Object *pop(VM *vm) {
    assert(vm->stackSize > 0, "Stack underflow!");
    return vm->stack[--vm->stackSize];
}

void mark(Object *object) {
    /* If already marked, we're done. Check this first to avoid recursing
       on cycles in the object graph. */
    if (object->marked) return;

    object->marked = 1;

    if (object->type == ObjectType::OBJ_PAIR) {
        mark(object->head);
        mark(object->tail);
    }
}

void markAll(VM *vm) {
    for (int i = 0; i < vm->stackSize; i++) {
        mark(vm->stack[i]);
    }
}

void sweep(VM *vm) {
    Object **object = &vm->firstObject;
    while (*object) {
        if (!(*object)->marked) {
            /* This object wasn't reached, so remove it from the list and free it. */
            Object *unreached = *object;

            *object = unreached->next;
            free(unreached);

            vm->numObjects--;
        } else {
            /* This object was reached, so unmark it (for the next GC) and move on to
             the next. */
            (*object)->marked = 0;
            object = &(*object)->next;
        }
    }
}

void gc(VM *vm) {
    int numObjects = vm->numObjects;

    markAll(vm);
    sweep(vm);

    vm->maxObjects = vm->numObjects == 0 ? INIT_OBJ_NUM_MAX : vm->numObjects * 2;

    printf("Collected %d objects, %d remaining.\n", numObjects - vm->numObjects,
           vm->numObjects);
}

Object *newObject(VM *vm, ObjectType type) {
    if (vm->numObjects == vm->maxObjects) gc(vm);

    auto *object = static_cast<Object *>(malloc(sizeof(Object)));
    object->type = type;
    object->next = vm->firstObject;
    vm->firstObject = object;
    object->marked = 0;

    vm->numObjects++;

    return object;
}

void pushInt(VM *vm, int intValue) {
    Object *object = newObject(vm, ObjectType::OBJ_INT);
    object->value = intValue;

    push(vm, object);
}

Object *pushPair(VM *vm) {
    Object *object = newObject(vm, ObjectType::OBJ_PAIR);
    object->tail = pop(vm);
    object->head = pop(vm);

    push(vm, object);
    return object;
}

void freeVM(VM *vm) {
    vm->stackSize = 0;
    gc(vm);
    free(vm);
}