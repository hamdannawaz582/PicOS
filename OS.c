#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/exception.h"
#include "exceptions.h"
#include "fs.h"
#include "init.h"
#include "uart.h"
#include "kmalloc.h"

Proc * current = NULL;

void loadInitProc() {
    uart_write("Loading Test Proc\n");
    Proc * procptr = kmalloc(sizeof(Proc));
    procptr->PID = globalPID++;
    procptr->state = RUNNING;
    current = procptr;
    procptr->stackbase = kmalloc(512); // 512 bytes for now
    procptr->sp = procptr->stackbase + 512;

    __asm volatile (
      "msr psp, %0\n"
      "mrs r0, control\n"
      "movs r1, #2\n" // I hate thumb16
      "orr r0, r0, r1\n"
      "msr control, r0\n"
      "isb\n"
      : 
      : "r"((uint32_t)procptr->sp)
      : "r0", "r1"
    );

    init();
}

int main() {
    u_init();
    uart_write("\n\n\n\n"
       "\033[1;32m"  // Bold green
       "============================================================\n"
       "======================  KERNEL STARTED  ====================\n"
       "========================   PicOS   =========================\n"
       "============================================================\n"
       "\033[0m"  // Reset
       "\n\n\n\n"
    );

    

    uart_write("\033[1;32m"  // Bold green
       "Setting Exception Handlers...\n"
       "\033[0m"  // Reset
    );
    exception_set_exclusive_handler(SVCALL_EXCEPTION, svc_handler_entry);
    exception_set_exclusive_handler(PENDSV_EXCEPTION, pendsv_handler_entry);
    
    uart_write("\033[1;32m"  // Bold green
       "Initiating Scheduler...\n"
       "\033[0m"  // Reset
    );
    initScheduler();


    uart_write("\033[1;32m"  // Bold green
       "Initiating Filesystem...\n"
       "\033[0m"  // Reset
    );
    int err = fs_init();

    uart_write("\033[1;32m"  // Bold green
       "Running Init Process...\n"
       "\033[0m"  // Reset
    );

    loadInitProc();

    uart_write("\n\n");
    
    fs_close();
}
