/* exceptions.h - SVCall_Handler, PSV_Handler */
#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include "RP2040.h"
#include "core_cm0plus.h"
#include "stdio.h"
#include "pico/stdlib.h"

#include "scheduler.h"
#include "proc.h"
#include "ksvc.h"

extern void svc_handler_entry(void);
extern void pendsv_handler_entry(void);
extern void pendsv_handler_end(uint32_t *stackframe, uint32_t lr);

/*----------------------------------------------------------------------
 * SVCall_Handler - calls respective SVC implementation based on number 
 * Input: 
 *  stackframe  -   Top of the process stackframe
 *  lr          -   Link register of the calling proc    
 *                                                           
 * Output:        
 *                                                       
 ----------------------------------------------------------------------*/
void SVCall_Handler(uint32_t *stackframe, uint32_t lr) {
    uint32_t r0 = stackframe[0]; // syscall number
    printf("Hit syscall %d\n", r0);
    printf("LR = %#010x\n", lr);
    printf("xPSR = %#010x\n", stackframe[7]);
    switch (r0) {
        case SYSCALL_YIELD:
            sys_yield();
            break;
        case SYSCALL_EXIT:
            sys_exit();
            break;
        case SYSCALL_GETPID:
            sys_getpid(stackframe);
            break;
        case SYSCALL_READ:

            break;
        case SYSCALL_WRITE:

            break;
        case SYSCALL_KILL:
            sys_kill(stackframe[1]);
            break;
    }
}

/*----------------------------------------------------------------------
 * PSV_Handler - saves old process, sets new one for loading
 * Input: 
 *  stackframe  -   Top of the process stackframe
 *  lr          -   Link register of the calling proc     
 *                                                          
 * Output:
 *  %r0         -   Top of stackframe of new proc
 *  %r1         -   Link register of new proc                                                               
 ----------------------------------------------------------------------*/
void PSV_Handler(uint32_t *stackframe, uint32_t lr) {
    printf("PendSV frfr ong\n");
    if (current->PID != 0) {
        
    }
    Proc * np = next(stackframe, lr);
    SCB->ICSR = SCB_ICSR_PENDSVCLR_Msk;
    pendsv_handler_end(np->sp, np->lr);
}

#endif