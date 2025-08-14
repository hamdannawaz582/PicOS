/* alloc.c - kmem_init, kmalloc, kfree, kbrk */

#include <stdbool.h>
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

static bool merge_blocks(mem_block * a, mem_block * b) {
    if (a + a->size != b) {
        return false; // Non-mergeable
    }

    a->next = b->next;
    a->size += b->size + sizeof(mem_block);
    return true;
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
    if ((uint32_t)addr % sizeof(mem_block) != 0) {
        DEBUG_PRINT("kfree: Invalid address %x", (uint32_t)addr);
        return;
    }

    mem_block * returnaddr = (mem_block *)addr;
    returnaddr = returnaddr - 1;

    if (returnaddr->size <= 0 || returnaddr->size > 512 - sizeof(mem_block)) {
        DEBUG_PRINT("kfree: Invalid size at address %x", (uint32_t)addr);
        return;
    }

    if ((void *)(returnaddr->next) >= kheap_ptr || (uint8_t *)returnaddr->next < &__kheap_start) {
        DEBUG_PRINT("kfree: Invalid next at address %x", (uint32_t)addr);
        return;
    }

    mem_block * current = mem_block_head;
    mem_block * prev = NULL;

    if (current == NULL) {
        mem_block_head = returnaddr;
        return;
    }

    while ((current->next != NULL) && current < returnaddr) {
        prev = current;
        current = (mem_block *)current->next;
    }

    if (current->next == NULL) {
        current->next = (uint32_t *)returnaddr;
        return;
    }

    if (!prev) {
        returnaddr->next = (uint32_t *)mem_block_head;
        mem_block_head = returnaddr;
        merge_blocks(mem_block_head, (mem_block *)mem_block_head->next);
        return;
    }

    if (current == returnaddr) {
        DEBUG_PRINT("kfree: Possible double free %x", (uint32_t)addr);
        return;
    }

    returnaddr->next = prev->next;
    prev->next = (uint32_t *)returnaddr;
    if (merge_blocks(prev, (mem_block *)prev->next)) {
        merge_blocks(prev, (mem_block *)prev->next);
        return;
    }

    merge_blocks(returnaddr, (mem_block *)returnaddr->next);

    return;
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