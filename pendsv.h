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
        "bne use_psp\n"
        "mrs r0, msp\n"
        "b done\n"
        "use_psp:\n"
        "mrs r0, psp\n"
        "done:\n"
        "mov r1, lr\n"
        "b PendSV_Handler\n"
    );
}

void PendSV_Handler(uint32_t *stackframe, uint32_t lr) {
    if (currentPID != 0) {
        Proc * cp = getHead(runningQueue);
        cp->lr = lr;
        cp->sp = stackframe;
    }
}

#endif