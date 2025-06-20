## Short Term
- [x] exit, kill, getpid, yield SVCalls & Process Termination
- [x] Proc 0
- [x] Loading procs from functions
- [x] Context Switching & Scheduling (FCFS)
- [x] Write, Read SVCalls
- [x] Loading embedded PIC ELFs
- [ ] Pre-emptive scheduling (Round Robin)
- [x] Refactoring exceptions to a single exceptions.h file
- [x] Filesystem (littleFS)
- [ ] close, fstat, isatty, open, stat, unlink, link, lseek SVCalls
- [ ] Loading PIC ELFs from FS
- [ ] Basic shell
- [ ] Way to send files to board (over UART)
- [ ] HardFault handling
- [ ] Update Write & Read SVCalls to work with files
- [x] Add XINU-ish style comments

## Long Term
- [ ] Semaphores
- [ ] Multiple virtual terminals
- [ ] fork, exec, sbrk, environ, times, wait SVCalls
- [ ] Refactoring to move all board/CPU specific code to separate files
- [ ] Adding newlib
- [ ] Output mechanisms besides UART
- [ ] Expose PIO to user
- [ ] Writing bitstreams to GPIO
- [ ] Replacing pico-sdk with custom code