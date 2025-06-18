#include "SVC.h"

void main(void) {
	// kill(2);
    // exit(0);
    int i = 0;
    while (1) {
        __asm volatile (
                "movs r0, #99\n"
                "svc #0\n"
        );
        if (i == 5) {
            i = 0;
            __asm volatile (
                "movs r0, #2\n"
                "svc #0\n"
        );
        }
        i++;
    }
    
}
