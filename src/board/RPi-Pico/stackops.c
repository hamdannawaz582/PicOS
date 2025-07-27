/* stackops.c - init_stack */

#include <stdint.h>

#include "util/klibc.h"

// I think this isn't portable enough, might have to rewrite scheduler into board/
// TODO: Rewrite scheduler's create proc function to be in board/ since it's somewhat board dependent
void init_stack(uint32_t *stack, uint32_t entry_point) {
    // DEBUG_PRINT("Putting xPSR @ %x\n", (uint32_t)stack + 15*sizeof(*stack));
    stack[15] = 0x41000000; // Dummy xPSR value i got off of another process
    stack[14] = entry_point;
}
