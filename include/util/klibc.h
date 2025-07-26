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

#endif // KLIBC_H
