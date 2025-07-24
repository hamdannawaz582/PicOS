## Feature Parity Goals
#### Meant to bring kernel to the same level as other branches

- [x] Move over boot code (init/main.c, board/vtable.S)
- [ ] Create a proper Makefile
- [ ] Move over linker script (board/linker.ld)
- [ ] Move over UART code (board/uart.c)
- [ ] Move kernel from flash to RAM via boot.S
- [x] Move over interrupt handling code (kernel/exceptions.c)
- [ ] Move over scheduler and process code (kernel/scheduler.c, proc.h)
- [ ] Move over SVCall code (kernel/svc.c)
- [ ] Move over kernel utils (util/klibc.c)
- [ ] Write tests
- [ ] Add IPC (kernel/ipc.c)
- [ ] Write a proper HardFault handler (kernel/exception.S)

## Main Goals
- [ ] Add services (to go from kernel code to user code)
- [ ] Add all required newlib SVCalls
  - [ ] write
  - [ ] read
  - [ ] open
  - [ ] close
  - [ ] lseek
  - [ ] fstat
  - [ ] stat
  - [ ] link
  - [ ] unlink
  - [ ] getpid
  - [ ] fork
  - [ ] execve
  - [ ] wait
  - [ ] kill
  - [ ] exit
  - [ ] isatty
  - [ ] sbrk
  - [ ] times
- [ ] Add driver support
- [ ] Figure out a way to load user init
- [ ] Add a bootstrap mode