# exception.s - svc_handler_entry, pendsv_handler_entry #
.syntax unified
.thumb_func
.cpu cortex-m0plus

.global svc_handler_entry
.extern SVCall_Handler

.global pendsv_handler_entry
.extern PSV_Handler
.global pendsv_handler_end

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
    mov r0, lr // link register
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
    b SVCall_Handler

.syntax unified
.thumb_func
.cpu cortex-m0plus
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
    b PSV_Handler

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
    nop