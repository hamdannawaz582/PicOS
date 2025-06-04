#ifndef PROC_H
#define PROC_H

typedef struct Proc {
    uint16_t PID;
    uint16_t state;
    uint32_t * stackbase;
    uint32_t * sp;
} Proc;

#endif