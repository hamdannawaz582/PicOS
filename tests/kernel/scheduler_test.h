#ifndef SCHEDULER_TEST
#define SCHEDULER_TEST

#include <stdbool.h>
#include <util/klibc.h>

#include "kernel/proc.h"
#include "kernel/scheduler.h"

static void test_proc() {
    while (true) {

    }
}

uint32_t testProcStack[32];

bool test_scheduler_init() {
    bool passed = true;
    for (int i = 0; i < MAX_PROC; i++) {
        if (proc_table[i].state != PROC_STATE_INACTIVE) {
            DEBUG_PRINT("Proc %x not set to PROC_STATE_INACTIVE", i);
            passed = false;
        }
    }

    scheduler_init();

    if (proc_table[0].state != PROC_STATE_READY) {
        DEBUG_PRINT("Proc %x not set to PROC_STATE_READY", 0);
        passed = false;
    }

    return passed;
}

bool test_add_proc(void) {
    bool passed = true;
    add_proc(0, (uint32_t)testProcStack, (uint32_t)(testProcStack + 31 - 15), -1, (PROC_FLAG_FLASH), (uint32_t)test_proc);

    if (proc_table[1].state != PROC_STATE_READY) {
        DEBUG_PRINT("Proc %x not set to PROC_STATE_READY", 1);
        passed = false;
    } else if (proc_table[1].PPID != 0) {
        DEBUG_PRINT("Proc %x PPID set incorrectly", 1);
        passed = false;
    }

    return passed;
}

bool test_get_next_proc(void) {

}

bool test_kill_proc(void) {

}

bool test_block_proc(void) {

}

#endif
