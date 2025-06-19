#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/clocks.h"
#include "hardware/uart.h"
#include "scheduler.h"
#include "queues.h"
#include "hardware/exception.h"
#include "malloc.h"
#include "RP2040.h"
#include "core_cm0plus.h"
#include "exceptions.h"
#include "elf.h"
#include "ProjectTemplate/program.h"
#include "fs.h"

Proc * current = NULL;

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
                "svc #3\n"
                "movs r0, #0\n"
            ); // exit syscall
        }
    }
}

void p1(void) {
    int i = 0;
    while (1) {
        sleep_ms(1000);
        i++;
        if (i == 5) {
            i = 0;
            __asm volatile (
                "movs r0, #2\n"
                "svc #2\n"
            );
        } else {
            __asm volatile (
                "movs r0, #15\n"
                "svc #15\n"
            );
        }
    }
}

void p2(void) {
    int i = 0;
    while (1) {
        sleep_ms(1000);
        i++;
        if (i == 5) {
            __asm volatile (
                "movs r0, #4\n"
                "movs r1, #1\n"
                "svc #2\n"
                "movs r0, #2\n"
                "svc #2\n"
            );
        } else {
            __asm volatile (
                "movs r0, #16\n"
                "svc #16\n"
            );
        }
    }
}

void p3(void) {
    int i = 0;
    while (1) {
        sleep_ms(1000);
        i++;
        if (i == 5) {
            i = 0;
            __asm volatile (
                "movs r0, #2\n"
                "svc #2\n"
            );
        } else {
            __asm volatile (
                "movs r0, #17\n"
                "svc #17\n"
            );
        }
    }
}
void loadTestProc() {
    printf("Loading Test Proc\n");
    Proc * procptr = malloc(sizeof(Proc));
    procptr->PID = globalPID++;
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

    printf("\n\n\n\n"
       "\033[1;32m"  // Bold green
       "============================================================\n"
       "======================  KERNEL STARTED  ====================\n"
       "========================   PicOS   =========================\n"
       "============================================================\n"
       "\033[0m"  // Reset
       "\n\n\n\n"
    );

    printf("\033[1;32m"  // Bold green
       "Setting Exception Handlers...\n"
       "\033[0m"  // Reset
    );
    exception_set_exclusive_handler(SVCALL_EXCEPTION, svc_handler_entry);
    exception_set_exclusive_handler(PENDSV_EXCEPTION, pendsv_handler_entry);
    
    printf("\033[1;32m"  // Bold green
       "Initiating Scheduler...\n"
       "\033[0m"  // Reset
    );

    printf("\033[1;32m"  // Bold green
       "Initiating Filesystem...\n"
       "\033[0m"  // Reset
    );
    int err = fs_init();

    printf("\n\n");
    
    initScheduler();
    createProc(p1, 512);
    createProc(p2, 512);
    createProc(p3, 512);
    loadProgramFromELF((uint32_t)program_elf);
    loadTestProc();

    fs_close();
}
