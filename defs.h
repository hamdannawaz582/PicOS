#ifndef DEFS_H
#define DEFS_H

// Limits
#define MAXFILE 5

// SVCall Numbers
#define SYSCALL_WRITE 0
#define SYSCALL_READ 1
#define SYSCALL_YIELD 2
#define SYSCALL_EXIT 3
#define SYSCALL_KILL 4
#define SYSCALL_GETPID 5

// Errors
    // FILE I/O
    #define EINVAL -1 // File does not exist
    #define EFLIMIT -2 // Max number of files open

#endif