#ifndef SYSCALLS_H
#define SYSCALLS_H

#include "stdio.h"

__attribute__((naked)) void syscall_handler(void) {
    __asm volatile (
        ".syntax unified\n"
        ".thumb\n"
        ".cpu cortex-m0plus\n"
        "mov r0, lr\n"
        "movs r1, #4\n"
        "tst r0, r1\n"
        // "ite eq\n"
        // "mrseq r0, msp\n"
        // "mrsne r0, psp\n"
        // "b SVCall_Handler\n"
        "bne use_psp\n"
        "mrs r0, msp\n"
        "b done\n"
        "use_psp:\n"
        "mrs r0, psp\n"
        "done:\n"
        "mov r1, lr\n"
        "b SVCall_Handler\n"
    );
}

void SVCall_Handler(uint32_t *stackframe, uint32_t lr) {
    uint32_t r0 = stackframe[0]; // syscall number
    printf("Hit syscall %d\n", r0);
    printf("LR = %#010x\n", lr);
    printf("xPSR = %#010x\n", stackframe[7]);
    switch (r0) {
        case 10:
            
            break;
    }
}

#endif