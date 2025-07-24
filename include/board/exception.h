/* exception.h - svc_handler_entry, svcall_handler, pendsv_handler_entry, pendsv_handler, pendsv_handler_end, systick_handler_entry, systick_handler, hardfault_handler_entry, hardfault_handler, nmi_handler, ir_handler */

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <stdint.h>

/*----------------------------------------------------------------------
 * svc_handler_entry - entry point to the SVC handler                
 * Input:       
 *                                                        
 * Output:                                                              
 *  %r0 - Bottom of the stack of calling process                         
 *  %r1 - Link register of calling process                               
 ----------------------------------------------------------------------*/
extern void svc_handler_entry(void);

/*----------------------------------------------------------------------
 * SVCall_Handler - calls respective SVC implementation based on number 
 * Input: 
 *  stackframe  -   Top of the process stackframe
 *  lr          -   Link register of the calling proc    
 *                                                           
 * Output:        
 *                                                       
 ----------------------------------------------------------------------*/
void svcall_handler(uint32_t *stackframe, uint32_t lr);

/*----------------------------------------------------------------------
 * pendsv_handler_entry - entry point to the PendSV handler                
 * Input:       
 *                                                        
 * Output:                                                              
 *  %r0 - Bottom of the stack of calling process                         
 *  %r1 - Link register of calling process                               
 ----------------------------------------------------------------------*/
extern void pendsv_handler_entry(void);

/*----------------------------------------------------------------------
 * PendSV_Handler - saves old process, sets new one for loading
 * Input: 
 *  stackframe  -   Top of the process stackframe
 *  lr          -   Link register of the calling proc     
 *                                                          
 * Output:
 *  %r0         -   Top of stackframe of new proc
 *  %r1         -   Link register of new proc                                                               
 ----------------------------------------------------------------------*/
uint32_t * pendsv_handler(uint32_t *stackframe, uint32_t lr);

/*----------------------------------------------------------------------
 * pendsv_handler_end - end point to the PendSV handler                   
 * Input:
 *  %r0 - Bottom of the new stack pointer
 *  %r1 - New link register       
 *                                                        
 * Output:                                                              
 *                                                          
 ----------------------------------------------------------------------*/
extern void pendsv_handler_end(void);

/*----------------------------------------------------------------------
 * systick_handler_entry - entry point to the SysTick handler                   
 * Input:       
 *                                                        
 * Output:                                                              
 *                               
 ----------------------------------------------------------------------*/
extern void systick_handler_entry(void);

/*----------------------------------------------------------------------
 * Systick_Handler - does nothing (like me) 
 * Input:
 * 
 * Output:
 *                             
 ----------------------------------------------------------------------*/
void systick_handler(void);

/*----------------------------------------------------------------------
 * systick_handler_entry - entry point to the HardFault handler                   
 * Input:       
 *                                                        
 * Output:                                                              
 *                               
 ----------------------------------------------------------------------*/
extern void hardfault_handler_entry(void);

/*----------------------------------------------------------------------
 * HardFault_Handler - does nothing (like me) 
 * Input:
 * 
 * Output:
 *                             
 ----------------------------------------------------------------------*/
void hardfault_handler(void);

/*----------------------------------------------------------------------
 * nmi_handler - handler for nonmaskable interrupts
 * Input:
 *  
 * Output:
 *                                           
 ----------------------------------------------------------------------*/
extern void nmi_handler(void);

/*----------------------------------------------------------------------
 * ir_handler - interrupt handler for interrupts 0 through 31
 * Input:
 *
 * Output:
 *           
 ----------------------------------------------------------------------*/
extern void ir_handler(void);

#endif