#include <cstdio>

#include "vm/vm.h"

void test1() {
    printf("Test 1: Objects on stack are preserved.\n");
    auto vm = new VM();
    vm->pushInt(1);
    vm->pushInt(2);

    vm->gc();
    VM::assert(vm->numObjects == 2, "Should have preserved objects.");
    vm->freeVM();
    delete (vm);
}

void test2() {
    printf("Test 2: Unreached objects are collected.\n");
    auto vm = new VM();
    vm->pushInt(1);
    vm->pushInt(2);
    vm->pop();
    vm->pop();

    vm->gc();
    VM::assert(vm->numObjects == 0, "Should have collected objects.");
    vm->freeVM();
    delete (vm);
}

void test3() {
    printf("Test 3: Reach nested objects.\n");
    auto vm = new VM();
    vm->pushInt(1);
    vm->pushInt(2);
    vm->pushPair();
    vm->pushInt(3);
    vm->pushInt(4);
    vm->pushPair();
    vm->pushPair();

    vm->gc();
    VM::assert(vm->numObjects == 7, "Should have reached objects.");
    vm->freeVM();
    delete (vm);
}

void test4() {
    printf("Test 4: Handle cycles.\n");
    auto vm = new VM();
    vm->pushInt(1);
    vm->pushInt(2);
    Object *a = vm->pushPair();
    vm->pushInt(3);
    vm->pushInt(4);
    Object *b = vm->pushPair();

    /* Set up a cycle, and also make 2 and 4 unreachable and collectible. */
    a->tail = b;
    b->tail = a;

    vm->gc();
    VM::assert(vm->numObjects == 4, "Should have collected objects.");
    vm->freeVM();
    delete (vm);
}

void perfTest() {
    printf("Performance Test.\n");
    auto vm = new VM();

    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 20; j++) {
            vm->pushInt(i);
        }

        for (int k = 0; k < 20; k++) {
            vm->pop();
        }
    }
    vm->freeVM();
    delete (vm);
}

int main() {
    test1();
    test2();
    test3();
    test4();
    perfTest();

    return 0;
}