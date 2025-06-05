#include "scheduler.h"
#include "pico/stdlib.h"
#include "malloc.h"

int currentPID = 0;

CircularQueue * runningQueue = NULL;
CircularQueue * blockedQueue = NULL;
Proc * p0 = NULL;

void initScheduler() {
    // Allocating Queues
    runningQueue = malloc(sizeof(CircularQueue));
    runningQueue->head = runningQueue->tail = NULL;
    blockedQueue = malloc(sizeof(CircularQueue));
    blockedQueue->head = blockedQueue->tail = NULL;
    
    // Generating P0
    p0 = malloc(sizeof(Proc));
    p0->PID = 0;
    p0->stackbase = malloc(128); // Why not
    p0->sp = p0->stackbase + 128;
    p0->lr = 0xfffffffd;
    p0->sp[7] = 0x41000000; // Dummy xPSR value i got off of another process
    p0->sp[6] = (uint32_t) proc0; // PC set to proc0
    p0->state = READY;
}

Proc *next() {
    Proc * n = popHead(runningQueue);
    n = (n == NULL)?(p0):(n); // Just run P0 if no other proc
    n->state = RUNNING;
    return n;
}

void add(Proc * toAdd) {
    if (toAdd->state == KILLED) return; // TODO: Free memory
    toAdd->state = READY;
    addProcToQueue(toAdd, runningQueue);
}

void proc0() {
    while (1)
        __asm volatile (
            "wfi"
        );
}