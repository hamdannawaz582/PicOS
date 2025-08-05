/* alloc.h - mem_block, kmem_init, kmalloc, kfree, kbrk */

#ifndef ALLOC_H
#define ALLOC_H

#include <stdint.h>
#include <stddef.h>

extern uint8_t __kheap_start;
extern uint8_t __uheap_start;

extern void * kheap_ptr;
extern void * uheap_ptr;

typedef struct mem_block {
    uint32_t size; // in bytes
    uint32_t * next;
} mem_block;

extern mem_block * mem_block_head;

/*----------------------------------------------------------------------
 * kmem_init   -   sets up kernel allocator and reserves 2.5 kB RAM
 * Input:
 *
 * Output:
 *
 ----------------------------------------------------------------------*/
void kmem_init(void);

/*----------------------------------------------------------------------
 * kmalloc      -   allocates memory from kernel heap
 * Input:
 *  size    -   number of bytes to allocate
 * Output:
 *  void *  -   void pointer to start of allocated memory or NULL
 ----------------------------------------------------------------------*/
void * kmalloc(size_t size);

/*----------------------------------------------------------------------
 * kfree    -   frees allocated memory
 * Input:
 *  addr    -   start of memory to free
 * Output:
 *
 ----------------------------------------------------------------------*/
void kfree(void * addr);

/*----------------------------------------------------------------------
 * kbrk     -   reserves blocks of memory for the kernel heap
 * Input:
 *
 * Output:
 *  mem_block *   -   pointer to reserved block of memory
 ----------------------------------------------------------------------*/
mem_block * kbrk(void);

#endif //ALLOC_H
