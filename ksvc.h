/*  ksvc.h - sys_write, sys_read, sys_yield, sys_exit, sys_kill, sys_getpid */
#ifndef KSVC_H
#define KSVC_H

#define SYSCALL_WRITE 0
#define SYSCALL_READ 1
#define SYSCALL_YIELD 2
#define SYSCALL_EXIT 3
#define SYSCALL_KILL 4
#define SYSCALL_GETPID 5

#include "pico/stdlib.h"
#include "stdio.h"

#include "proc.h"
#include "scheduler.h"

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

inline void sys_kill(int pid) {

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