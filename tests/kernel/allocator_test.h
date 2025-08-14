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

void * p1, * p2, * p3, * p4, * p5, * p6;

bool test_allocator_malloc() {
    if (kmalloc(0) != NULL) {
        return false;
    }

    p1 = kmalloc(512 - sizeof(mem_block));
    p2 = kmalloc(512 - sizeof(mem_block));
    p3 = kmalloc(512 - sizeof(mem_block));
    memset(p1, 0xFF, 512 - sizeof(mem_block));
    memset(p2, 0xFF, 512 - sizeof(mem_block));
    memset(p3, 0xFF, 512 - sizeof(mem_block));

    p4 = kmalloc(512 - sizeof(mem_block));
    p5 = kmalloc(512 - sizeof(mem_block));
    p6 = kmalloc(512 - sizeof(mem_block));
    memset(p4, 0xFF, 512 - sizeof(mem_block));
    memset(p5, 0xFF, 512 - sizeof(mem_block));
    memset(p6, 0xFF, 512 - sizeof(mem_block));

    if (p1 == p2) {
        return false;
    }

    if (p3 == p4) {
        return false;
    }

    if (p5 == p6) {
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

bool test_allocator_free() {
    kfree(p1);
    kfree(p2);
    kfree(p6);
    kfree(p4);
    kfree(p3);
    kfree(p5);

    if (mem_block_head != p1 - sizeof(mem_block)) {
        return false;
    }

    mem_block * current = mem_block_head;
    current = (mem_block *)(current->next);
    if (current != p2 - sizeof(mem_block)) {
        return false;
    }

    // I'm realizing I probably should have made an array, but I'm too far in to change it now

    current = (mem_block *)(current->next);
    if (current != p3 - sizeof(mem_block)) {
        return false;
    }

    current = (mem_block *)(current->next);
    if (current != p4 - sizeof(mem_block)) {
        return false;
    }

    current = (mem_block *)(current->next);
    if (current != p5 - sizeof(mem_block)) {
        return false;
    }

    current = (mem_block *)(current->next);
    if (current != p6 - sizeof(mem_block)) {
        return false;
    }

    return true;
}

// TODO: Add tests for block merging

#endif //ALLOCATOR_TEST_H
