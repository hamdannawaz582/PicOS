/* interrupt.h - svcall_handler, memory_fault_handler, illegal_instruction_handler, interrupt_handler */
#ifndef PICOS_INTERRUPT_H
#define PICOS_INTERRUPT_H

#include <stdint.h>

/*----------------------------------------------------------------------
 * svcall_handler   -   dispatches svcall with proper arguments
 * Input:
 *  uint32_t*   -   stack pointer of caller
 * Output:
 *  uint32_t*   -   stack pointer of process to continue
 ----------------------------------------------------------------------*/
uint32_t * svcall_handler(uint32_t * stack);

/*----------------------------------------------------------------------
 * memory_fault_handler   -   handles illegal memory access
 * Input:
 *  uint32_t*   -   stack pointer of caller
 * Output:
 *  uint32_t*   -   stack pointer of process to continue
 ----------------------------------------------------------------------*/
uint32_t * memory_fault_handler(uint32_t * stack);

/*----------------------------------------------------------------------
 * illegal_instruction_handler   -   handles illegal instructions
 * Input:
 *  uint32_t*   -   stack pointer of caller
 * Output:
 *  uint32_t*   -   stack pointer of process to continue
 ----------------------------------------------------------------------*/
uint32_t * illegal_instruction_handler(uint32_t * stack);

/*----------------------------------------------------------------------
 * generic_sysfault_handler   -   generic catch-all fault handler
 * Input:
 *  uint32_t*   -   stack pointer of caller
 * Output:
 *  uint32_t*   -   stack pointer of process to continue
 ----------------------------------------------------------------------*/
uint32_t * generic_sysfault_handler(uint32_t * stack);

/*----------------------------------------------------------------------
 * interrupt_handler   -   handles generic interrupts
 * Input:
 *  uint32_t*   -   stack pointer of caller
 * Output:
 *  uint32_t*   -   stack pointer of process to continue
 ----------------------------------------------------------------------*/
uint32_t * interrupt_handler(uint32_t * stack);

#endif //PICOS_INTERRUPT_H