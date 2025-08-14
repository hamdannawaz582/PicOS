/* alloc.c - kmem_init, kmalloc, kfree, kbrk */

#include <kernel/alloc.h>
#include <stddef.h>
#include <kernel/panic.h>

#include "kernel/kdef.h"

void * kheap_ptr = NULL;
void * uheap_ptr = NULL;

mem_block * mem_block_head = NULL;

void kmem_init(void) {
    // Get 5 blocks of memory from the kernel heap allocator
    kheap_ptr = &__kheap_start;
    uheap_ptr = &__uheap_start;

    mem_block * start = kbrk();
    mem_block * current = start;
    mem_block_head = start;
    for (int i = 0; i < 4; i++) {
        current->next = (uint32_t *)(kbrk());
        current = (mem_block *)(current->next);
    }
}

void * kmalloc(size_t size) {
    if (size <= 0) {
        return NULL;
    }

    if (mem_block_head == NULL) {
        kbrk();
    }

    if (size % sizeof(mem_block) != 0) {
        size += sizeof(mem_block) - (size % sizeof(mem_block));
    }

    mem_block * current = mem_block_head;
    mem_block * chosen = NULL;
    mem_block * prev = NULL;

    while (current->next != NULL) {
        if (current->size >= size) {
            chosen = current;
            break;
        }
        prev = current;
        current = (mem_block *)current->next;
    }

    if (chosen == NULL) {
        current->next = (uint32_t *)(kbrk());
        return kmalloc(size);
    }

    if (chosen->size == size) {
        if (prev) {
            prev->next = chosen->next;
        } else {
            mem_block_head = (mem_block *)chosen->next;
        }
        return chosen + 1;
    }

    mem_block * chosen_next = (mem_block *)chosen->next;
    chosen->next = (uint32_t *)((char *)chosen + size);

    *((mem_block *)(chosen->next)) = (mem_block) {
        .next = (uint32_t *)chosen_next,
        .size = chosen->size - size - sizeof(mem_block),
    };

    chosen->size = size;

    if (((mem_block *)chosen->next)->size == 0) {
        if (prev) prev->next = ((mem_block *)(chosen->next))->next;
        else mem_block_head = (mem_block *)((mem_block *)(chosen->next))->next;

        return chosen + 1;
    }

    if (prev) {
        prev->next = chosen->next;
    } else {
        mem_block_head = (mem_block *)chosen->next;
    }

    return chosen + 1;
}

void kfree(void * addr) {

}

mem_block * kbrk(void) {
    if (kheap_ptr + 512 > uheap_ptr) {
        PANIC("Out of memory :(");
    }

    void * kptr = kheap_ptr;

    kheap_ptr += 512;

    ((mem_block *)kptr)->next = NULL;
    ((mem_block *)kptr)->size = 512 - sizeof(mem_block);

    return (mem_block *)kptr;
}