/* uart_recv.c - tty_getc, tty_gets, tty_is_readable */

#include <kernel/config.h>

#ifdef CONFIG_TTY_RECV_UART

#include <driver/tty.h>

#ifndef USE_UART1
    #define UART_BASE 0x40034000
    #define UART_RST_BIT 22
#else
    #define UART_BASE 0x40038000
    #define UART_RST_BIT 23
#endif

char tty_getc(void) {
    volatile uint32_t flagregister = UART_BASE + 0x18;
    while (*(uint32_t *)flagregister & (1 << 4));

    return *(volatile uint32_t *)UART_BASE & 0xFF;
}

int32_t tty_gets(char *s, size_t n) {
    for (int i = 0; i < n; i++) {
        char c = tty_getc();
        // uart_write_c(c); // echo
        if (c == '\r') { // clearing \r\n (ew)
            s[i] = 0;
            // uart_read_c();
            // uart_write_c('\n');
            return 0;
        }
        s[i] = c;
    }

    return 0;
}

int32_t tty_is_readable(void) {

    return 0;
}

#endif