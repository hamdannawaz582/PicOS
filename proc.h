#ifndef PROC_H
#define PROC_H

#define RUNNING 1
#define BLOCKED 0
#define READY 2
#define KILLED -1

typedef struct Proc {
    uint16_t PID;
    uint16_t state;
    uint32_t * stackbase;
    uint32_t * sp;
    uint32_t lr;
} Proc;

#endif