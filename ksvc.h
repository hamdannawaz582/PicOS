/*  ksvc.h - sys_write, sys_read, sys_yield, sys_exit, sys_kill, sys_getpid */
#ifndef KSVC_H
#define KSVC_H

#include "pico/stdlib.h"
#include "stdio.h"

#include "proc.h"
#include "scheduler.h"
#include "defs.h"

/*----------------------------------------------------------------------
 * sys_write - writes a buffer to stdout                                
 * Input:
 *  dest    -   File/Console to write to (unused)
 *  buffer  -   Buffer to write
 *  count   -   Bytes to write
 *                                                                
 * Output:
 *                                                               
 ----------------------------------------------------------------------*/
inline void sys_write(int dest, char * buffer, int count) {
    printf("%.*s\n", count, buffer);
}

/*----------------------------------------------------------------------
 * sys_read - reads in a buffer from stdin                                
 * Input:
 *  dest    -   File/Console to read from (unused)
 *  buffer  -   Buffer to read to
 *  count   -   Bytes to read
 *                                                                
 * Output:
 *                                                               
 ----------------------------------------------------------------------*/
inline void sys_read(int source, char * buffer, int count) {
    scanf("%.*s", count, buffer);
}

/*----------------------------------------------------------------------
 * sys_yield - sets PendSV bit to request context switch
 * Input:
 *  
 * Output:
 *                 
 ----------------------------------------------------------------------*/
inline void sys_yield(void) {
    SCB->ICSR = SCB_ICSR_PENDSVSET_Msk;
}

/*----------------------------------------------------------------------
 * sys_exit - sets proc's status to KILLED and requests context switch
 * Input: 
 * 
 * Output:
 *  
 ----------------------------------------------------------------------*/
inline void sys_exit(void) {
    current->state = KILLED;
    SCB->ICSR = SCB_ICSR_PENDSVSET_Msk;
}

/*----------------------------------------------------------------------
 * sys_kill - kills process with given PID
 * Input: 
 *  pid     -   PID of process to kill
 * Output:
 *  
 ----------------------------------------------------------------------*/
inline void sys_kill(uint32_t pid) {
    if (pid == current->PID) {
        current->state = KILLED;
        SCB->ICSR = SCB_ICSR_PENDSVSET_Msk;
    } else {
        // TODO: Deal with memory
        Proc * result = removeProcFromQueue(pid, runningQueue); // Not freeing right now I have some ideas for this for later
    }
}

/*----------------------------------------------------------------------
 * sys_getpid - returns PID of running process
 * Input:
 *  stackframe  -   stack frame of the caller
 * 
 * Output:
 *  %r0         -   PID of running process                          
 ----------------------------------------------------------------------*/
inline void sys_getpid(uint32_t * stackframe) {
    stackframe[0] = current->PID;
}
#endif