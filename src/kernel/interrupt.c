/* interrupt.c - svcall_handler, memory_fault_handler, illegal_instruction_handler, interrupt_handler */

#include <kernel/interrupt.h>
#include <kernel/scheduler.h>
#include <kernel/panic.h>
#include <stdint.h>

extern uint32_t * extract_svcall_args(uint32_t * stack);

uint32_t * svcall_handler(uint32_t * stack) {
    proc_table[current_proc].stack_ptr = (uint32_t)stack;
    DEBUG_PRINT("Servicing SVC #%d from Proc %d", *(extract_svcall_args(stack)), current_proc);
    return stack;
}

uint32_t * memory_fault_handler(uint32_t * stack) {

}

uint32_t * illegal_instruction_handler(uint32_t * stack) {

}

uint32_t * generic_sysfault_handler(uint32_t * stack) {
    PANIC("Hardfaulted :(");
}

uint32_t * interrupt_handler(uint32_t * stack) {

}