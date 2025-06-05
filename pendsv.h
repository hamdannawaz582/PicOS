#ifndef PENDSV_H
#define PENDSV_H
#include "scheduler.h"
#include "stdio.h"
#include "pico/stdlib.h"
#include "proc.h"

__attribute__((naked)) void pendsv_handler(void) {
    __asm volatile (
        ".syntax unified\n"
        ".thumb\n"
        ".cpu cortex-m0plus\n"
        "mov r0, lr\n"
        "movs r1, #4\n"
        "tst r0, r1\n"
        "bne use_psp2\n"
        "mrs r0, msp\n"
        "b done2\n"
        "use_psp2:\n"
        "mrs r0, psp\n"
        "done2:\n"
        "mov r1, lr\n"
        "b PSV_Handler\n"
    );
}

void PSV_Handler(uint32_t *stackframe, uint32_t lr) {
    printf("PendSV frfr ong\n");
    if (current->PID != 0) {
        
    }
    SCB->ICSR = SCB_ICSR_PENDSVCLR_Msk;
}

#endif