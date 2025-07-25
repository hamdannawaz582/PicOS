/* tty.c - tty_init, tty_putchar, tty_puts, tty_getc, tty_gets, tty_is_readable */

#include <stddef.h>
#include <stdint.h>
#include <kernel/kdef.h>

__attribute__((weak)) int32_t tty_init(void) {
    return -EINVAL;
}

__attribute__((weak)) int32_t tty_putchar(char c) {
    return -EINVAL;
}

__attribute__((weak)) int32_t tty_puts(const char *s) {
    return -EINVAL;
}

__attribute__((weak)) char tty_getc(void) {
    return -EINVAL;
}

__attribute__((weak)) int32_t tty_gets(char *s, size_t n) {
    return -EINVAL;
}

__attribute__((weak)) int32_t tty_is_readable(void) {
    return -EINVAL;
}