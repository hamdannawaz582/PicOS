/*  ksvc.h - sys_write, sys_read, sys_yield, sys_exit, sys_kill, sys_getpid, sys_getppid, sys_open, sys_close */
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

/*----------------------------------------------------------------------
 * sys_getppid - returns PID of parent process                          
 * Input:
 *  stackframe  -   stack frame of the caller
 * 
 * Output: 
 *  %r0         -   PID of parent process
 ----------------------------------------------------------------------*/
inline void sys_getppid(uint32_t * stackframe) {
    stackframe[0] = current->PPID;
}

/*----------------------------------------------------------------------
 * sys_open     -   open a file
 * Input: 
 *  stackframe  -   stack frame of the caller
 * 
 * Output: 
 *  %r0         -   FD of opened file if successful, errorno if failed
 ----------------------------------------------------------------------*/
inline void sys_open(uint32_t * stackframe) {
    int i = 2;
    for (; i < MAXFILE; i++) {
        if (current->FDTable[i] == NULL) break;
    }

    // If no slots available raise error
    if (i == MAXFILE) {
        stackframe[0] = EFLIMIT;
        return;
    }

    current->FDTable[i] = malloc(sizeof(lfs_file_t));
    int err = lfs_file_open(&fs, current->FDTable[i], (const char *)stackframe[1], stackframe[2]);
    if (err) {
        stackframe[0] = EINVAL;
    } else {
        stackframe[0] = 0;
    }
}

/*----------------------------------------------------------------------
 * sys_close - closes an open file                                      
 * Input:
 *  stackframe  -   stack frame of the caller
 * 
 * Output: 
 *  %r0         -   0 if successful, errorno if not
 ----------------------------------------------------------------------*/
inline void sys_close(uint32_t * stackframe) {
    // Check to see if FD is in range of closable
    if (stackframe[1] < 2 || stackframe[1] > 4) {
        stackframe[0] = EINVAL;
        return;
    }

    // Check to see if file is even open
    if (current->FDTable[stackframe[1]] == NULL) {
        stackframe[0] = EINVAL;
        return;
    }

    lfs_file_close(&fs, current->FDTable[stackframe[1]]);
    current->FDTable[stackframe[1]] = NULL;
    stackframe[0] = 0;
}


#endif