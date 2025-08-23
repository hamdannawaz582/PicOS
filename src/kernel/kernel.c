#include <kernel/config.h>
#include <driver/tty.h>
#include <util/klibc.h>
#include <kernel/proc.h>


int main(void) {
    KERNEL_PRINT("Kernel Process loaded");
    __asm volatile (
            "mov r1, #0\n"
            "svc #0\n"
            :
            :
            : "r0"
            );
    while(1) {

    }
}