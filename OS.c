#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/clocks.h"
#include "hardware/uart.h"
#include "scheduler.h"
//#include "scheduler.c"
#include "queues.h"
//#include "queues.c"
//#include "syscalls.h"
#include "hardware/exception.h"
#include "malloc.h"
#include "RP2040.h"
#include "core_cm0plus.h"
//#include "pendsv.h"
#include "exceptions.h"

void make_svcall(uint32_t num) {
    switch (num) {
        case 0:
            __asm volatile (
                "movs r0, #0\n"
                "svc #0\n"
            );
            break;
        case 1:
            __asm volatile (
                "movs r0, #1\n"
                "svc #0\n"
            );
            break;
    }
}

void blinker() {
    int i = 0;
    while (1) {
        make_svcall(0);
        sleep_ms(1000);
        i++;
        if (i == 5) {
            __asm volatile (
                "movs r0, #2\n"
                "svc #2\n"
                "movs r0, #0\n"
            ); // exit syscall
        }
    }
}

void loadTestProc() {
    printf("Loading Test Proc\n");
    Proc * procptr = malloc(sizeof(Proc));
    procptr->PID = 1;
    procptr->state = RUNNING;
    current = procptr;
    procptr->stackbase = malloc(512); // 512 bytes for now
    procptr->sp = procptr->stackbase + 512;
    // addProcToQueue(procptr, runningQueue);
    __set_PSP((uint32_t)procptr->sp);
    __set_CONTROL(__get_CONTROL() | (1 << 1));
    __ISB();
    blinker();
}

int main() {
    stdio_init_all();

    exception_set_exclusive_handler(SVCALL_EXCEPTION, svc_handler_entry);
    exception_set_exclusive_handler(PENDSV_EXCEPTION, pendsv_handler_entry);
    
    initScheduler();
    loadTestProc();
}
