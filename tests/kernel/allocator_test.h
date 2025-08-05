#ifndef ALLOCATOR_TEST_H
#define ALLOCATOR_TEST_H

#include <kernel/alloc.h>
#include <stddef.h>

#include "../../include/kernel/alloc.h"
#include "kernel/kdef.h"

bool test_allocator_init() {
    kmem_init();

    mem_block * head = mem_block_head;

    for (int i = 0; i < 4; i++) {
        if (head->next == NULL) {
            return false;
        }
        head = (mem_block *)head->next;
    }

    if (head->next != NULL) {
        return false;
    }

    return true;
}

bool test_allocator_malloc() {
    if (kmalloc(0) != NULL) {
        return false;
    }

    if (kmalloc(512 - sizeof(mem_block)) == kmalloc(512 - sizeof(mem_block))) {
        return false;
    }

    if (kmalloc(1) == NULL || kmalloc(1) == (void *)-ENOMEM) {
        return false;
    }

    if (kmalloc(1) == kmalloc(1)) {
        return false;
    }

    return true;
}

#endif //ALLOCATOR_TEST_H
