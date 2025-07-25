/* uart_init.c - tty_init */

#include <kernel/config.h>

#if defined(CONFIG_TTY_RECV_UART) || defined(CONFIG_TTY_SEND_UART)

#include <driver/tty.h>

#ifndef USE_UART1
    #define UART_BASE 0x40034000
    #define UART_RST_BIT 22
#else
    #define UART_BASE 0x40038000
    #define UART_RST_BIT 23
#endif

#define RESET 0x4000c000
#define RESET_SET RESET + 0x2000
#define RESET_CLR RESET + 0x3000
#define RESET_DONE RESET + 0x8
#define PERI_CLOCK 0x40008000 + 0x48
#define UART_CONTROL UART_BASE + 0x30
#define UART_LCR UART_BASE + 0x2c
#define USERBANK_IO 0x40014000

int32_t tty_init(void) {
    *(volatile uint32_t *)(RESET_CLR) = (1 << 5); // Clearing reset on I/O bank 0

    while (!(*(volatile uint32_t *)(RESET_DONE) & (1 << 5)));

    *(volatile uint32_t *)(RESET_SET) = (1 << UART_RST_BIT); // Resetting the UART
    *(volatile uint32_t *)(RESET_CLR) = (1 << UART_RST_BIT); // Bringing the UART out of reset


    __asm volatile (
        "uartrst:"
        "mov r0, #0x4\n"
        "lsl r0, r0, #16\n"
        "mov r1, #0xc\n"
        "orr r0, r0, r1\n"
        "lsl r0, r0, #12\n"
        "ldr r1, [r0, #8]\n"
        "mov r0, r1\n"
        "movs r1, #1\n"
        "lsl r1, r1, #22\n"
        "and r1, r1, r2\n"
        "beq uartrst\n"
        :
        :
        : "r0", "r1", "r2"
    );

    *(volatile uint32_t *)(PERI_CLOCK) = (1 << 11) | (1 << 7); // Enabling clock and setting crystal oscillator

    *(volatile uint32_t *)(UART_CONTROL) = 0;

    // Setting Baud rate to 115200
    // Peripheral Clock Frequency / (16 * 115200) = 6.5104166667
    // We need to set 6 into UARTIBRD and 0.51*64 + 0.5 = 33 into UARTFBRD
    *(volatile uint32_t *)(UART_BASE + 0x24) = 6;
    *(volatile uint32_t *)(UART_BASE + 0x28) = 33;

    *(volatile uint32_t *)(UART_CONTROL) =
        (1 << 9) | // Enabling UART receive
        (1 << 8) | // Enabling UART transmit
        (1 << 0);  // Enabling UART as a whole

    *(volatile uint32_t *)(UART_LCR) =
    // Setting word length to 8
    (1 << 6) | (1 << 5) |
    // Turning on FIFOs
    (1 << 4);

    // Assigning UART to GPIOs
    #ifndef USE_UART1
        *(volatile uint32_t *)(USERBANK_IO + 0x4) = 2;
        *(volatile uint32_t *)(USERBANK_IO + 0x0c) = 2;
    #else
        *(volatile uint32_t *)(USERBANK_IO + 0x24) = 2;
        *(volatile uint32_t *)(USERBANK_IO + 0x2c) = 2;
    #endif

    return 0;
}

#endif
