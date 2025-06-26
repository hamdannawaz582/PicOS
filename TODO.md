### Current SDK usage
- Bootloader
- Setting exception handler
- UART
- Flash reading and writing
- System register setting (PENDSV, Control, PSP/MSP)
- malloc/free
- printf

### Roadmap
- [x] Replacing printf with custom UART write function
- [x] Replacing getchar/putchar with custom implementations
- [x] Replacing malloc/free calls with hardcoded arrays
- [x] Setting system registers manually
- [ ] Basic hardfault handler definition
- [ ] Basic systick definition
- [ ] Setting interrupt vector table manually
- [ ] Booting manually (using the existing pico bootloader) + Makefile
- [ ] Relocating kernel from flash to RAM
- [ ] Flash reading/writing
- [ ] Sleep (dread)

### What won't be replaced
- malloc/free need a libc and _sbrk to work, both will be implemented in a later step in a later branch
- printf isn't really necessary for kernel debug messages, but if needed I will implement one that can print hex addresses
- flash handling won't be as safe as the Pico SDK because the SDK moves to RAM from XIP to execute flash functions, the kernel will reside entirely in RAM so that is not necessary