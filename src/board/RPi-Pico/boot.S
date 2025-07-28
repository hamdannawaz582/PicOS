.syntax unified
.cpu cortex-m0plus

.global bss_zero
.extern __bss_start
.extern __bss_end
.extern kinit

.thumb_func
bss_zero:
    ldr r0, =__bss_start
    ldr r1, =__bss_end
    movs r2, #0

    l:
    cmp r1, r0
    blt end
        str r2, [r0]
        adds r0, #4

    b l

    end:
        bl kinit