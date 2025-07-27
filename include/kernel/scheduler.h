/* scheduler.h - scheduler_init, get_next_proc, add_proc, remove_proc */

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <kernel/proc.h>

#define PROC_FLAG_MUST_RESTART 0
#define PROC_FLAG_SYS_PANIC 1
#define PROC_FLAG_SERVICE 2
#define PROC_FLAG_FLASH 3
#define PROC_FLAG_NICE 4

#define SCHED_RUNNING_QUEUE MAX_PROC
#define SCHED_BLOCKED_QUEUE MAX_PROC+1

extern uint8_t current_proc;

/*----------------------------------------------------------------------
 * scheduler_init   -   sets up scheduler and queues proc 0
 * Input:
 *
 * Output:
 *
 ----------------------------------------------------------------------*/
void scheduler_init();

/*----------------------------------------------------------------------
 * get_next_proc   -   gets the next process from queue, requeues current
 * Input:
 *
 * Output:
 *  proc_t* - pointer to next process
 ----------------------------------------------------------------------*/
proc_t * get_next_proc();

/*----------------------------------------------------------------------
 * add_proc        -   adds process to ready queue
 * Input:
 *  parent        - parent PID
 *  stack_base    - start of stack memory
 *  stack_pointer - current stack pointer
 *  ELF_base      - start of ELF file in memory
 *  flags         - flags
 *  entry_point   - entry point of program
 * Output:
 *  uint32_t      - -ENOMEM if no more space, else address of proc_t
 ----------------------------------------------------------------------*/
uint32_t add_proc(uint8_t parent, uint32_t stack_base, uint32_t stack_pointer, uint32_t ELF_base, uint8_t flags, uint32_t entrypoint);

/*----------------------------------------------------------------------
 * remove_proc   -   removes process from queues
 * Input:
 *  PID          -   PID of process to remove
 * Output:
 *  proc_t*      -   pointer to removed process
 ----------------------------------------------------------------------*/
proc_t * remove_proc(uint8_t PID);

#endif
