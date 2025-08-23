.cpu cortex-m0plus
.thumb

.extern _sptr // Linker defined symbol
.extern kinit
.extern nmi_handler
.extern hardfault_handler
.extern svc_handler
.extern pendsv_handler
.extern systick_handler
.extern ir_handler
.extern _dummy // Linker defined symbol
.extern bss_zero

.section .vtable, "ax"

.word _sptr     // Stack Pointer
.word bss_zero     // Reset Handler
.word nmi_handler
.word hardfault_handler
.word _dummy
.word _dummy
.word _dummy
.word _dummy
.word _dummy
.word _dummy
.word _dummy
.word svc_handler
.word _dummy
.word _dummy
.word pendsv_handler
.word systick_handler
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