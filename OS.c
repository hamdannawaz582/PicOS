#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/exception.h"
#include "RP2040.h"
#include "core_cm0plus.h"
#include "exceptions.h"
#include "fs.h"
#include "init.h"

Proc * current = NULL;

void loadInitProc() {
    printf("Loading Test Proc\n");
    Proc * procptr = malloc(sizeof(Proc));
    procptr->PID = globalPID++;
    procptr->state = RUNNING;
    current = procptr;
    procptr->stackbase = malloc(512); // 512 bytes for now
    procptr->sp = procptr->stackbase + 512;
    __set_PSP((uint32_t)procptr->sp);
    __set_CONTROL(__get_CONTROL() | (1 << 1));
    __ISB();
    init();
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
    initScheduler();


    printf("\033[1;32m"  // Bold green
       "Initiating Filesystem...\n"
       "\033[0m"  // Reset
    );
    int err = fs_init();

    printf("\033[1;32m"  // Bold green
       "Running Init Process...\n"
       "\033[0m"  // Reset
    );

    loadInitProc();

    printf("\n\n");
    
    fs_close();
}
