/* exceptions.h - svcall_handler, pendsv_handler, systick_handler, hardfault_handler */

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdint.h>

void svcall_handler(uint32_t *stackframe, uint32_t lr) {
    
}

uint32_t * pendsv_handler(uint32_t *stackframe, uint32_t lr) {
    
}

void systick_handler(void) {

}

void hardfault_handler(void) {

}

#endif