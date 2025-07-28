/* scheduler.c - proc0, scheduler_init, get_next_proc, add_proc, remove_proc */

#include <kernel/scheduler.h>
#include <kernel/kdef.h>
#include <stdint.h>
#include <stddef.h>
#include <kernel/proc.h>

#include "kernel/panic.h"
#include <stddef.h>

extern void init_stack(uint32_t *stack, uint32_t entry_point);

proc_t proc_table[MAX_PROC + 2] = {0};
uint8_t current_proc = 0;

char p0stack[128];
void proc0() {
    while (1)
        __asm volatile (
            "wfi"
        );
}

void scheduler_init() {
    // Nothing in blocked queue/list
    proc_table[SCHED_BLOCKED_QUEUE].next = proc_table[SCHED_RUNNING_QUEUE].prev = -1;

    // DEBUG_PRINT("P0 Stack base = %x, Stack pointer = %x", p0stack, p0stack + 124 - 15 * sizeof(size_t));
    if (add_proc(-1, (uint32_t)p0stack, (uint32_t)(p0stack + 124 - 15*sizeof(size_t)), -1, (PROC_FLAG_SYS_PANIC | PROC_FLAG_NICE | PROC_FLAG_FLASH), (uint32_t)proc0)
        == -ENOMEM) {
        PANIC("Could not allocate Proc 0\n");
    }

    current_proc = 0; // Process 0
}

proc_t * get_next_proc() {

}

// TODO: Rewrite this to make it less awkward
uint32_t add_proc(uint8_t parent, uint32_t stack_base, uint32_t stack_pointer, uint32_t ELF_base, uint8_t flags, uint32_t entrypoint) {
    // DEBUG_PRINT("Adding Proc [Summary]\n" "stack base = %x\n stack_pointer = %x\n entry = %x\n", stack_base, stack_pointer, entrypoint);
    // Finding an empty slot in the proc_table

    int8_t pid = -1;
    for (int i = 0; i < MAX_PROC; i++) {
        if (proc_table[i].state == PROC_STATE_INACTIVE) {
            // DEBUG_PRINT("Chose slot %x", i);
            pid = i;
            break;
        }
    }

    if (pid == -1) {
        return -ENOMEM;
    }

    proc_table[pid].PPID = parent;
    proc_table[pid].stack_base = stack_base;
    proc_table[pid].stack_ptr = stack_pointer;
    proc_table[pid].ELF_base = ELF_base;
    proc_table[pid].flags = flags;
    proc_table[pid].state = PROC_STATE_READY;

    // init_stack((uint32_t *)proc_table[pid].stack_ptr, entrypoint);
    return pid;
}

proc_t * remove_proc(uint8_t PID) {
    if (PID >= MAX_PROC || PID < 0 || proc_table[PID].state == PROC_STATE_INACTIVE) {
        return (proc_t *)(-EINVAL);
    }

    proc_table[PID].state = PROC_STATE_INACTIVE;
    return &proc_table[PID];
}
