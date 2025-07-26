/* uart_send.c - tty_putchar, tty_puts, tty_clear */

#include <kernel/config.h>

#ifdef CONFIG_TTY_SEND_UART

#include <driver/tty.h>
#include <stdint.h>

#ifndef USE_UART1
    #define UART_BASE 0x40034000
    #define UART_RST_BIT 22
#else
    #define UART_BASE 0x40038000
    #define UART_RST_BIT 23
#endif

int32_t tty_putchar(char c) {
    volatile uint32_t flagregister = UART_BASE + 0x018;

    if (c == '\n') c = '\r';

    print:
    while (*(uint32_t *)flagregister & (1 << 5));

    *(volatile uint32_t *)UART_BASE = c;

    if (c == '\r') {
        c = '\n';
        goto print;
    }

    return 0;
}

int32_t tty_puts(const char *s) {
    for (; *s; s++) {
        if (*s == '\n') {
            tty_putchar('\r');
        }
        tty_putchar(*s);
    }

    return 0;
}

int32_t tty_clear(void) {

    return 0;
}

#endif