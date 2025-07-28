/* loader.h - load_kernel, load_proc_from_elf, load_proc_from_fptr */
#ifndef LOADER_H
#define LOADER_H

#include <stdint.h>

/*----------------------------------------------------------------------
 * load_kernel - loads the kernel (hehe)
 * Input:
 *  entry_point -   entry_point of the kernel process
 * Output:
 *
 ----------------------------------------------------------------------*/
void load_kernel(void * entry_point);

/*----------------------------------------------------------------------
 * load_proc_from_elf - loads a process from an elf file
 * Input:
 *  elf        -    start of elf file
 *  stackstart -    start of the stack
 *  stacksize  -    size of the stack
 * Output:
 *  uint32_t   -    -EINVAL if ELF file is not valid, -ENOMEM if no space
 ----------------------------------------------------------------------*/
uint32_t load_proc_from_elf(void * elf, uint32_t stackstart, uint32_t stacksize);

/*----------------------------------------------------------------------
 * load_proc_from_fptr - loads a process from a function pointer
 * Input:
 *  entry_point-    entry function of the program
 *  stackstart -    start of the stack
 *  stacksize  -    size of the stack
 * Output:
 *  uint32_t   -    -EINVAL if ELF file is not valid, -ENOMEM if no space
 ----------------------------------------------------------------------*/
uint32_t load_proc_from_fptr(void * entry_point, uint32_t stackstart, uint32_t stacksize);

#endif //LOADER_H
