/* SVC.h read, write, exit, yield, getpid, kill */
#ifndef SVC_H
#define SVC_H

#include "../defs.h"

/*----------------------------------------------------------------------
 * read - reads count chars from fd into buffer                         
 * Input:
 *  fd      -   File to read from
 *  buffer  -   Buffer to read into
 *  count   -   Number of chars to read in 
 *                                                               
 * Output:  
 *  int     -   success/failure                                                            
 ----------------------------------------------------------------------*/
int read(int fd, char * buffer, int count) {
    register int r0 __asm__("r0") = SYSCALL_READ;
    register int r1 __asm__("r1") = fd;
    register int r2 __asm__("r2") = (unsigned int) buffer;
    register int r3 __asm__("r3") = count;
    register int r02 __asm__("r0");

    __asm volatile (
        "svc #0\n"
        : "=r" (r02)
        : "r"(r0), "r"(r1), "r"(r2), "r"(r3)
    );
    return r02;
}

/*----------------------------------------------------------------------
 * write - writes count chars from buffer to fd                        
 * Input:
 *  fd      -   File to write to
 *  buffer  -   Buffer to write from
 *  count   -   Number of chars to write   
 *                                                             
 * Output:  
 *  int     -   success/failure                                                            
 ----------------------------------------------------------------------*/
int write(int fd, char * buffer, int count) {
    register int r0 __asm__("r0") = SYSCALL_WRITE;
    register int r1 __asm__("r1") = fd;
    register int r2 __asm__("r2") = (unsigned int) buffer;
    register int r3 __asm__("r3") = count;
    register int r02 __asm__("r0");

    __asm volatile (
        "svc #0\n"
        : "=r" (r02)
        : "r"(r0), "r"(r1), "r"(r2), "r"(r3)
    );
    return r02;
}

/*----------------------------------------------------------------------
 * exit - return from current process
 * Input:
 *  out     -   return val
 * 
 * Output:
 *                                    
 ----------------------------------------------------------------------*/
__attribute__((naked)) void exit(int out) {
    __asm volatile (
        "movs r0, #3\n"
        "svc #0\n"
    );
}

/*----------------------------------------------------------------------
 * yield - yield processing to another process
 * Input:
 * 
 * Output:
 *                                    
 ----------------------------------------------------------------------*/
void yield(void) {
    int callNum = SYSCALL_YIELD;
    __asm volatile (
        "movs r0, %0\n"
        "svc #0\n"
        : "=r"(callNum)
        : "r"(callNum)
    );
}

/*----------------------------------------------------------------------
 * getpid - get own PID
 * Input:
 * 
 * Output:
 *  int     -   PID of caller                                
 ----------------------------------------------------------------------*/
int getpid(void) {
    register int r0 __asm__("r0") = SYSCALL_GETPID;
    register int r02 __asm__("r0");

    __asm volatile (
        "svc #0\n"
        : "=r" (r02)
        : "r"(r0)
    );
    return r02;
}

/*----------------------------------------------------------------------
 * kill - kill a running process
 * Input:
 *  pid     -   PID of process to kill
 * 
 * Output:
 *  int     -   success/failure                                   
 ----------------------------------------------------------------------*/
int kill(int pid) {
    register int r0 __asm__("r0") = SYSCALL_KILL;
    register int r1 __asm__("r1") = pid;
    register int r02 __asm__("r0");

    __asm volatile (
        "svc #0\n"
        : "=r" (r02)
        : "r"(r0), "r"(r1)
    );
    return r02;
}

#endif