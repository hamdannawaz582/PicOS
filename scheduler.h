/* scheduler.h - proc0, initScheduler, add, next, createProc */
#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "proc.h"
#include "queues.h"

extern Proc * current;

CircularQueue * runningQueue = NULL;
CircularQueue * blockedQueue = NULL;
Proc * p0 = NULL;
int globalPID = 0;

/*----------------------------------------------------------------------
 * proc0 - process to be used when no other is available for scheduling 
 * Input: 
 * 
 * Output: 
 * 
 ----------------------------------------------------------------------*/
void proc0() {
    while (1)
        __asm volatile (
            "wfi"
        );
}

/*----------------------------------------------------------------------
 * initScheduler - sets up queues and proc0 before a process is loaded
 * Input:
 * 
 * Output:
 *   
 ----------------------------------------------------------------------*/
void initScheduler() {
    // Allocating Queues
    runningQueue = malloc(sizeof(CircularQueue));
    runningQueue->head = runningQueue->tail = NULL;
    blockedQueue = malloc(sizeof(CircularQueue));
    blockedQueue->head = blockedQueue->tail = NULL;
    
    // Generating P0
    p0 = malloc(sizeof(Proc));
    p0->PID = globalPID++;
    p0->stackbase = malloc(128); // Why not
    p0->sp = p0->stackbase + 128;
    p0->lr = 0xfffffffd;
    p0->sp[15] = 0x41000000; // Dummy xPSR value i got off of another process
    p0->sp[14] = (uint32_t) proc0; // PC set to proc0
    p0->state = READY;
}

/*----------------------------------------------------------------------
 * add - adds a process to the running queue 
 * Input:
 *  toAdd   -   process to add to the queue
 * 
 * Output:
 *                            
 ----------------------------------------------------------------------*/
void add(Proc * toAdd) {
    if (toAdd->state == KILLED) return; // TODO: Free memory
    toAdd->state = READY;
    addProcToQueue(toAdd, runningQueue);
}

/*----------------------------------------------------------------------
 * next - fetches the next process to be executed
 * Input:
 *  stackframe  -   stack pointer of the currently running process
 *  lr          -   link register of the currently running process
 * 
 * Output:
 *  Proc *      -   Pointer to process to be loaded next                       
 ----------------------------------------------------------------------*/
Proc *next(uint32_t * stackframe, uint32_t lr) {
    // Saving previous stack ptr and lr
    current->sp = stackframe;
    current->lr = lr;
    add(current);

    Proc * n = popHead(runningQueue);
    n = (n == NULL)?(p0):(n); // Just run P0 if no other proc
    n->state = RUNNING;
    
    current = n;
    return n;
}

/*----------------------------------------------------------------------
 * createProc - adds a new process to the ready queue
 * Input:
 *  fptr        -   pointer to the function to be called by new proc
 *  stacksize   -   stack size to be allocated for new proc
 * 
 * Output:
 *                     
 ----------------------------------------------------------------------*/
void createProc(void * fptr, uint32_t stacksize) {
    // TODO: Add support for command line arguments
    Proc * newProc = malloc(sizeof(Proc));
    newProc->PID = globalPID++;
    newProc->stackbase = malloc(stacksize);
    newProc->sp = newProc->stackbase + stacksize;
    newProc->lr = 0xfffffffd;
    newProc->sp[15] = 0x41000000; // Dummy xPSR value i got off of another process
    newProc->sp[14] = (uint32_t) fptr;
    newProc->state = READY;
    add(newProc);
}

#endif