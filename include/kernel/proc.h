/* proc.h - proc_t */

#ifndef PROC_H
#define PROC_H
#include <stdint.h>
#include <kernel/config.h>

#define PROC_STATE_INACTIVE 0
#define PROC_STATE_READY 1
#define PROC_STATE_RUNNING 2
#define PROC_STATE_BLOCKED 3
#define PROC_STATE_KILLED 4

typedef struct proc_t {
    uint8_t PPID;
    uint8_t state; // Ready, Running, Blocked, Killed, Inactive
    uint16_t EID;

    uint32_t stack_base;
    uint32_t stack_ptr;

    uint32_t ELF_base;

    uint8_t next;
    uint8_t prev;

    uint8_t flags;
    uint8_t queue;

    uint32_t FD_table[MAX_FILE];
} proc_t;

extern proc_t proc_table[MAX_PROC + 2]; // Running, Blocked

#endif