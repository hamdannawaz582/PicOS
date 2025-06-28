.cpu cortex-m0plus
.thumb

.extern _sptr
.extern kinit
.extern nmi_handler
.extern hardfault_handler_entry
.extern svc_handler_entry
.extern pendsv_handler_entry
.extern systick_handler_entry
.extern ir_handler
.extern _dummy

.section .vtable, "ax"

.word _sptr     // Stack Pointer
.word kinit     // Reset Handler
.word nmi_handler
.word hardfault_handler_entry
.word _dummy
.word _dummy
.word _dummy
.word _dummy
.word _dummy
.word _dummy
.word _dummy
.word svc_handler_entry
.word _dummy
.word _dummy
.word pendsv_handler_entry
.word systick_handler_entry
.word ir_handler
.word ir_handler
.word ir_handler
.word ir_handler
.word ir_handler
.word ir_handler
.word ir_handler
.word ir_handler
.word ir_handler
.word ir_handler
.word ir_handler
.word ir_handler
.word ir_handler
.word ir_handler
.word ir_handler
.word ir_handler
.word ir_handler
.word ir_handler
.word ir_handler
.word ir_handler
.word ir_handler
.word ir_handler
.word ir_handler
.word ir_handler
.word ir_handler
.word ir_handler
.word ir_handler
.word ir_handler
.word ir_handler
.word ir_handler
.word ir_handler
.word ir_handler