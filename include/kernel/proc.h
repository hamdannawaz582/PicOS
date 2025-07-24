/* proc.h - proc_t */

#ifndef PROC_H
#define PROC_H
#include <stdint.h>
#include <kernel/kdef.h>

typedef struct proc_t {
    uint16_t PID;
    uint16_t state;
    uint32_t * stackbase;
    uint32_t * sp;
    uint32_t lr;
    
    uint16_t PPID;
    uint32_t FDTable[MAXFILE];
} proc_t;

#endif