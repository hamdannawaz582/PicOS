/* klibc.h - kmalloc, kfree, memset, memcpy */
#ifndef KMALLOC_H
#define KMALLOC_H

#include <stdint.h>

#define MEMSTART 0x20040000
#define MEMEND 0x20042000

#ifndef NULL
    #define NULL 0
#endif

uint64_t memorymap = 0;
uint8_t allocated[64];

/*----------------------------------------------------------------------
 * kmalloc - allocates memory in 128 byte chunks
 * Input:
 *  size    -   amount of memory to allocate
 * 
 * Output:
 *  void *  -   starting address of allocated memory                        
 ----------------------------------------------------------------------*/
void * kmalloc(uint64_t size) {
    if (size == 0) return NULL;
    uint64_t memoryRequired = size + 128 - size%128;
    int memoryRegions = memoryRequired/128;

    uint64_t bitmap = 1;
    for (int i = 0; i < memoryRegions; i++) {
        bitmap *= 2;
    }

    bitmap -= 1;

    for (int i = 0; i < (64 - memoryRegions); i++) {
        if ((memorymap & (bitmap << i)) == 0) {
            memorymap |= (bitmap << i);
            allocated[i] = memoryRegions;
            return (void *)(i*128 + MEMSTART);
        }
    }

    return NULL;
}

/*----------------------------------------------------------------------
 * kfree - frees allocated memory
 * Input:
 *  toFree  -   memory to free
 * Output:
 *                                        
 ----------------------------------------------------------------------*/
void kfree(void * toFree) {
    uint8_t i = ((uint32_t)toFree - MEMSTART)/128;
    uint64_t bitmap = 1;
    for (int j = 0; j < allocated[i]; j++) {
        bitmap *= 2;
    }
    bitmap -= 1;
    bitmap = ~bitmap;

    memorymap &= (bitmap << i);

    return;
}

/*----------------------------------------------------------------------
 * memset - writes to memory location
 * Input:
 *  dest    -   location to write to
 *  b       -   value to write
 *  count   -   number of bytes to write                       
 ----------------------------------------------------------------------*/
void * memset(void * dest, uint8_t b, unsigned int count) {
    for (int i = 0; i < count; i++) {
        ((uint8_t *)dest)[i] = b;
    }
    return dest;
}

/*----------------------------------------------------------------------
 * memcpy - copies bytes from a source to a destination
 * Input:
 *  dest    -   location to write to
 *  src     -   location to read from
 *  count   -   number of bytes to write                 
 ----------------------------------------------------------------------*/
void * memcpy(void * dest, void * src, unsigned int count) {
    for (int i = 0; i < count; i++) {
        ((uint8_t *)dest)[i] = ((uint8_t *)src)[i];
    }
    return dest;
}

#endif