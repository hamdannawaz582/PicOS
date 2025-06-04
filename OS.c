#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/clocks.h"
#include "hardware/uart.h"
#include "scheduler.h"
#include "scheduler.c"
#include "syscalls.h"
#include "hardware/exception.h"

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

int main() {
    stdio_init_all();
    // TODO: setup interrupts
    // TODO: init syscalls
    exception_set_exclusive_handler(SVCALL_EXCEPTION, syscall_handler);
    
    initScheduler();
    printf("Testout \n");
    char buff[1024];
    sleep_ms(5000);
    make_svcall(0);
    printf("Returned From Syscall\n");

}
