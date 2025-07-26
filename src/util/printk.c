/* printk.c - printx, printk */

#include <stdarg.h>
#include <util/klibc.h>
#include <driver/tty.h>
#include <stdint.h>

void printx(uint32_t number) {
    char num[11];
    num[8] = 0;
    num[0] = '0';
    num[1] = 'x';
    char lookup[] = {'0', '1', '2', '3', '4', '5',
                     '6', '7', '8', '9', 'A', 'B',
                     'C', 'D', 'E', 'F'};

    for (int i = 9; i >= 2; i--) {
        num[i] = lookup[number % 16];
        number /= 16;
    }
    tty_puts(num);
}

void printk(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);

    for (fmt; *fmt; fmt++) {
        if (*fmt == '%') {
            fmt++;
            switch (*fmt) {
                case 's':
                    tty_puts(va_arg(ap, char *));
                    break;
                case 'c':
                    tty_putchar(va_arg(ap, int));
                    break;
                case 'd':
                    // This requires idiv, which this processor does not support,
                    // instead of doing a whole song and dance and using the fdiv
                    // from the pico bootrom, I'm just not going to print ints.
                    va_arg(ap, int);
                    break;
                case 'x':
                    printx(va_arg(ap, uint32_t));
            }
        } else {
            tty_putchar(*fmt);
        }
    }

    va_end(ap);
}
