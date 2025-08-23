/* exception.S - save_context, restore_context, svc_handler, pendsv_handler, systick_handler, hardfault_handler, nmi_handler, ir_handler */

.syntax unified
.cpu cortex-m0plus

.global svc_handler
.extern svcall_handler

.global pendsv_handler

.global systick_handler

.global hardfault_handler
.extern generic_sysfault_handler

.global nmi_handler

.global ir_handler

.thumb_func
 #----------------------------------------------------------------------
 # save_context - pushes registers onto PSP
 #
 # Input:
 #
 # Output:
 #  %psp        -   r4-r11
 #----------------------------------------------------------------------
save_context:
    mrs r0, psp
    subs r0, 32
    mov r1, r0
    stm r0!, {r4-r7}

    mov r4, r8
    mov r5, r9
    mov r6, r10
    mov r7, r11
    stm r0!, {r4-r7}

    mov r0, r1
    bx lr

.thumb_func
 #----------------------------------------------------------------------
 # restore_context - restores registers from PSP
 #
 # Input:
 #  %psp        -   r4-r11
 # Output:
 #  {r4-r11}    -   original context
 #----------------------------------------------------------------------
restore_context:
    mov r1, r0
    adds r0, 16

    ldm r0!, {r4-r7}
    mov r8, r4
    mov r9, r5
    mov r10, r6
    mov r11, r7

    mov r0, r1
    ldm r0!, {r4-r7}
    mov r0, r1
    adds r0, 32

    msr psp, r0
    bx lr

.thumb_func
 #----------------------------------------------------------------------
 # svc_handler - entry point to SVC exception handler
 #
 # Input:
 #
 # Output:
 #  %r0     -   return value of svc routine
 #----------------------------------------------------------------------
svc_handler:
    push {lr}
    bl save_context

    bl svcall_handler

    bl restore_context
    pop {r1}
    mov lr, r1
    bx lr


.thumb_func
 #----------------------------------------------------------------------
 # pendsv_handler - handles pendsv exception (by doing nothing)
 #
 # Input:
 #
 # Output:
 #
 #----------------------------------------------------------------------
pendsv_handler:
    bx lr

.thumb_func
 #----------------------------------------------------------------------
 # systick_handler - handles systick exception (by doing nothing)
 #
 # Input:
 #
 # Output:
 #
 #----------------------------------------------------------------------
systick_handler:
    bx lr

.thumb_func
 #----------------------------------------------------------------------
 # hardfault_handler - entry point to generic_sysfault_handler
 #
 # Input:
 #
 # Output:
 #
 #----------------------------------------------------------------------
hardfault_handler:
    bkpt
    bl generic_sysfault_handler

.thumb_func
 #----------------------------------------------------------------------
 # nmi_handler - handles non-maskable interrupt exception (by doing nothing)
 #
 # Input:
 #
 # Output:
 #
 #----------------------------------------------------------------------
nmi_handler:
    bx lr

.thumb_func
 #----------------------------------------------------------------------
 # ir_handler - handles generic interrupt exceptions (by doing nothing)
 #
 # Input:
 #
 # Output:
 #
 #----------------------------------------------------------------------
ir_handler:
    bx lr

