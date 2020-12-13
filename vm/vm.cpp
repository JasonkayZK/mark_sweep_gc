#include "vm.h"
#include <iostream>

VM::VM() {
    std::cout << "vm started!" << std::endl;
    this->stackSize = 0;
    this->firstObject = nullptr;
    this->numObjects = 0;
    this->maxObjects = INITIAL_GC_THRESHOLD;
}

VM::~VM() {
    std::cout << "all objects cleaned, vm closed!" << std::endl;
}

void VM::push(Object *value) {
    assert(this->stackSize < STACK_MAX, "Stack overflow!");
    this->stack[this->stackSize++] = value;
}

Object *VM::pop() {
    assert(this->stackSize > 0, "Stack underflow!");
    return this->stack[--this->stackSize];
}

void VM::mark(Object *object) {
    /* If already marked, we're done. Check this first to avoid recursively
       on cycles in the object graph. */
    if (object->marked) return;

    object->marked = 1;

    if (object->type == ObjectType::OBJ_PAIR) {
        mark(object->head);
        mark(object->tail);
    }
}

void VM::markAll() {
    for (int i = 0; i < this->stackSize; i++) {
        mark(this->stack[i]);
    }
}

void VM::sweep() {
    Object **object = &this->firstObject;
    while (*object) {
        if (!(*object)->marked) {
            /* This object wasn't reached, so remove it from the list and free it. */
            Object *unreached = *object;

            *object = unreached->next;
            delete (unreached);

            this->numObjects--;
        } else {
            /* This object was reached, so unmark it (for the next GC) and move on to
             the next. */
            (*object)->marked = 0;
            object = &(*object)->next;
        }
    }
}

void VM::gc() {
    int i_numObjects = this->numObjects;

    markAll();
    sweep();

    this->maxObjects = this->numObjects == 0 ? INITIAL_GC_THRESHOLD : this->numObjects * 2;

    printf("Collected %d objects, %d remaining.\n", i_numObjects - this->numObjects,
           this->numObjects);
}

Object *VM::newObject(ObjectType type) {
    if (this->numObjects == this->maxObjects) gc();

    auto *object = new Object();
    object->type = type;
    object->next = this->firstObject;
    this->firstObject = object;
    object->marked = 0;

    this->numObjects++;

    return object;
}

void VM::pushInt(int intValue) {
    Object *object = newObject(ObjectType::OBJ_INT);
    object->value = intValue;

    push(object);
}

Object *VM::pushPair() {
    Object *object = newObject(ObjectType::OBJ_PAIR);
    object->tail = pop();
    object->head = pop();

    push(object);
    return object;
}

void VM::freeVM() {
    this->stackSize = 0;
    gc();
}

void VM::assert(int condition, const char *message) {
    if (!condition) {
        std::cout << message << std::endl;
        exit(1);
    }
}
