/* tty.h - tty_init, tty_putchar, tty_puts, tty_getc, tty_gets, tty_is_readable */

#ifndef TTY_H
#define TTY_H

#include <stdint.h>
#include <stddef.h>

/*----------------------------------------------------------------------
 * tty_init - initializes chosen tty connection
 * Inputs:
 *
 * Outputs:
 *  int32_t - -EINVAL if driver undefined, 0 if defined
 ----------------------------------------------------------------------*/
int32_t tty_init(void);

/*----------------------------------------------------------------------
 * tty_put_char - write a character to tty
 * Input:
 *  c       - character to write
 *
 * Output:
 *  int32_t - -EINVAL if driver undefined, 0 if defined
 ----------------------------------------------------------------------*/
int32_t tty_putchar(char c);

/*----------------------------------------------------------------------
 * tty_puts - writes string to uart
 * Input:
 *  s       - string to write
 *
 * Output:
 *  int32_t - -EINVAL if driver undefined, 0 if defined
 ----------------------------------------------------------------------*/
int32_t tty_puts(const char *s);

/*----------------------------------------------------------------------
 * tty_clear - clears tty screen
 * Input:
 *
 * Output:
 *  int32_t - -EINVAL if driver undefined, 0 otherwise
 ----------------------------------------------------------------------*/
int32_t tty_clear(void);

/*----------------------------------------------------------------------
 * tty_getc - reads character from tty
 * Input:
 *
 * Output:
 * char - -EINVAL if driver undefined, character read otherwise
 ----------------------------------------------------------------------*/
char tty_getc(void);

/*----------------------------------------------------------------------
 * tty_gets - reads from tty into a string
 * Input:
 *  s - buffer to read into
 *  n - max size of buffer
 *
 * Output:
 *  int32_t - -EINVAL if driver undefined, 0 if defined
 ----------------------------------------------------------------------*/
int32_t tty_gets(char *s, size_t n);

/*----------------------------------------------------------------------
 * tty_is_readable - checks if tty has a character waiting
 * Input:
 *
 * Output:
 *  int32_t - -EINVAL if driver undefined, true or false otherwise
 ----------------------------------------------------------------------*/
int32_t tty_is_readable(void);

#endif //TTY_H
