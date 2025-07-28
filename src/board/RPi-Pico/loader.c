/* loader.c - load_kernel, load_proc_from_elf, load_proc_from_fptr */

#include <stdint.h>
#include <board/loader.h>
#include <kernel/kdef.h>

#include <kernel/scheduler.h>

#include "kernel/panic.h"
#include "util/klibc.h"

#define SRAM5_MID 0x20041500
#define SRAM_END 0x20042000

void load_kernel(void * entry_point) {
    int PPID = -1, ELF_Start = -1, StackStart = SRAM5_MID, StackPointer = SRAM_END;
    int flags = PROC_FLAG_FLASH | PROC_FLAG_SYS_PANIC;

    int PID = add_proc(PPID, StackStart, StackPointer, ELF_Start, flags, (uint32_t)entry_point);

    KERNEL_PRINT("Kernel Placed at PID %d", PID);

    if (PID <= 1 || PID > MAX_PROC) {
        PANIC("Kernel Process could not be loaded");
    }

    proc_table[PID].state = PROC_RUNNING;
    current_proc = PID;

    __asm volatile (
      "msr psp, %0\n"
      "mrs r0, control\n"
      "movs r1, #2\n" // I hate thumb16
      "orr r0, r0, r1\n"
      "msr control, r0\n"
      "isb\n"
      :
      : "r"((uint32_t)StackPointer)
      : "r0", "r1"
    );

    ((void (*) ())entry_point)();

}

uint32_t load_proc_from_elf(void * elf, uint32_t stackstart, uint32_t stacksize) {

    return -EINVAL;
}

uint32_t load_proc_from_fptr(void * entry_point, uint32_t stackstart, uint32_t stacksize) {

    return -EINVAL;
}