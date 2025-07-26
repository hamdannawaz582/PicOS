/* klibc.h - printk, memcpy, memset */

#ifndef KLIBC_H
#define KLIBC_H

#include <stddef.h>

/*----------------------------------------------------------------------
 * printk - allows formatted printing
 * Inputs:
 *  fmt     -   formatted string to print
 *  ...     -   list of args (string as char *, char, hex as uint32_t)
 * Outputs:
 *
 ----------------------------------------------------------------------*/
void printk(const char *fmt, ...);

/*----------------------------------------------------------------------
 * memcpy - copies memory from src to dest
 * Inputs:
 *  dest    -   destination to copy to
 *  src     -   source to copy from
 *  n       -   number of bytes to copy
 * Outputs:
 *
 ----------------------------------------------------------------------*/
void memcpy(void *dest, const void *src, size_t n);

/*----------------------------------------------------------------------
 * memcpy - sets memory at dest to c
 * Inputs:
 *  dest    -   destination to write to
 *  c       -   byte to write
 *  n       -   number of bytes to copy
 * Outputs:
 *
 ----------------------------------------------------------------------*/
void memset(void *dest, unsigned char c, size_t n);

// ANSI Color codes
#define RESET   "\033[0m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BRIGHT_BLACK   "\033[90m"
#define BRIGHT_RED     "\033[91m"
#define BRIGHT_GREEN   "\033[92m"
#define BRIGHT_YELLOW  "\033[93m"
#define BRIGHT_BLUE    "\033[94m"
#define BRIGHT_MAGENTA "\033[95m"
#define BRIGHT_CYAN    "\033[96m"
#define BRIGHT_WHITE   "\033[97m"

#define CLEAR_SCREEN "\033[2J\033[H"

#define KERNEL_PRINT(str, ...) \
    printk("[" BRIGHT_GREEN "KERN" RESET "]\t" str "\n", ##__VA_ARGS__);

#define DEBUG_PRINT(str, ...) \
    printk("[" BRIGHT_BLUE "DBUG" RESET "]\t" str "\n", ##__VA_ARGS__);

#endif // KLIBC_H
