# exception.s - svc_handler_entry, pendsv_handler_entry, pendsv_handler_end, systick_handler_entry, hardfault_handler_entry #
.syntax unified
.cpu cortex-m0plus

.global svc_handler_entry
.extern SVCall_Handler

.global pendsv_handler_entry
.extern PSV_Handler
.global pendsv_handler_end

.global systick_handler_entry
.extern Systick_Handler

.global hardfault_handler_entry
.extern HF_Handler

.global nmi_handler

.global ir_handler

.thumb_func
 #----------------------------------------------------------------------
 # svc_handler_entry - entry point to the SVC handler
 #                   
 # Input:       
 #                                                        
 # Output:                                                              
 #  %r0 - Bottom of the stack of calling process                         
 #  %r1 - Link register of calling process                               
 #----------------------------------------------------------------------
svc_handler_entry:
    mov r0, lr
    movs r1, #4

    # Check stack bit of lr
    tst r0, r1
    bne svc_psp

    svc_msp:
    mrs r0, msp 
    b svc_done

    svc_psp:
    mrs r0, psp 
    b svc_done

    svc_done:
    mov r1, r14
    push {lr}
    bl SVCall_Handler
    pop {r1}
    mov lr, r1
    bx lr

.thumb_func
 #----------------------------------------------------------------------
 # pendsv_handler_entry - entry point to the PendSV handler
 #                   
 # Input:       
 #                                                        
 # Output:                                                              
 #  %r0 - Bottom of the stack of calling process                         
 #  %r1 - Link register of calling process                               
 #----------------------------------------------------------------------
pendsv_handler_entry:
    mov r0, lr
    movs r1, #4
    
    # Check stack bit of lr
    tst r0, r1
    bne pendsv_psp

    pendsv_msp:
    mrs r0, msp
    b pendsv_done

    pendsv_psp:
    mrs r0, psp
    b pendsv_done

    pendsv_done:
    # Worst part of the project in my opinion, we have to push r4-r11 to
    # the stack but cortex-m0+ doesn't have STMDB, so instead we have to
    # manually decrement stack and use STM, but cortex-m0+ also cannot
    # use STM with registers r8-r11, so we have to move them to normal 
    # registers beforehand.
    # FIXME: Replace this monstrosity with STMDB when porting

    subs r0, #32 // making room on the stack
    mov r1, r0
    stm r0!, {r4-r7}
    # Here we go 
    mov r4, r8
    mov r5, r9
    mov r6, r10
    mov r7, r11
    stm r0!, {r4-r7}
    # Restoring decremented stack pointer
    mov r0, r1
    mov r1, lr
    push {lr}
    bl PSV_Handler
    pop {r1}
    mov lr, r1
    b pendsv_handler_end

.thumb_func
 #----------------------------------------------------------------------
 # pendsv_handler_end - end point to the PendSV handler
 #                   
 # Input:
 #  %r0 - Bottom of the new stack pointer
 #  %r1 - New link register       
 #                                                        
 # Output:                                                              
 #                                                          
 #----------------------------------------------------------------------
pendsv_handler_end:
    mov lr, r1
    # What's better than doing something horrific once? Doing it twice of
    # course, this does what we did in pendsv_handler_entry but in the
    # opposite direction to get the old stack back.
    mov r1, r0
    adds r0, #16
    ldm r0!, {r4-r7}
    mov r8, r4
    mov r9, r5
    mov r10, r6
    mov r11, r7
    mov r0, r1
    ldm r0!, {r4-r7}
    mov r0, r1
    adds r0, #32

    # Load PSP with the new stack pointer
    msr psp, r0

    # Remind xPSR we were in PendSV
    // mrs r2, xPSR
    // movs r0, #14 // 0xe 
    // orrs r2, r2, r0
    // msr xPSR, r2
    bx lr

.thumb_func 
 #----------------------------------------------------------------------
 # systick_handler_entry - entry point to the SysTick handler
 #                   
 # Input:       
 #                                                        
 # Output:                                                              
 #                               
 #----------------------------------------------------------------------
systick_handler_entry:
    push {lr}
    bl Systick_Handler
    pop {r1}
    mov lr, r1
    bx lr

.thumb_func
 #----------------------------------------------------------------------
 # systick_handler_entry - entry point to the HardFault handler
 #                   
 # Input:       
 #                                                        
 # Output:                                                              
 #                               
 #----------------------------------------------------------------------
hardfault_handler_entry:
    bkpt
    push {lr}
    bl HF_Handler
    pop {r1}
    mov lr, r1
    bx lr

.thumb_func
 #----------------------------------------------------------------------
 # nmi_handler - handler for nonmaskable interrupts
 # 
 # Input:
 #  
 # Output:
 #                                           
 #----------------------------------------------------------------------
 nmi_handler:
    bkpt
    bx lr

.thumb_func
 #----------------------------------------------------------------------
 # ir_handler - interrupt handler for interrupts 0 through 31
 #
 # Input:
 #
 # Output:
 #           
 #----------------------------------------------------------------------
ir_handler:
    bkpt
    bx lr