/*  ksvc.h - write, read, yield, exit, kill, getpid */
#ifndef KSVC_H
#define KSVC_H

#define SYSCALL_WRITE 0
#define SYSCALL_READ 1
#define SYSCALL_YIELD 2
#define SYSCALL_EXIT 3
#define SYSCALL_KILL 4
#define SYSCALL_GETPID 5

inline void write(int dest, char * buffer, int count) {

}

inline void read(int source, char * buffer, int count) {

}

inline void yield(void) {

}

inline void exit(void) {

}

inline void kill(int pid) {

}

inline int getpid(void) {
    return 0;
}
#endif