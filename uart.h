#ifndef UART_H
#define UART_H

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
#define CLOCK 0x40008000
#define PERI_CLOCK CLOCK + 0x48
#define UART_CONTROL UART_BASE + 0x30
#define UART_LCR UART_BASE + 0x2c
#define USERBANK_IO 0x40014000
#define XOSC_REG 0x40024000
#define XOSC_SET XOSC_REG + 0x2000

#include <stdbool.h>
#include <stdint.h>

/*----------------------------------------------------------------------
 * uart_write_c - write a character to uart
 * Input:
 *  c       -   character to write
 * 
 * Output:
 *                              
 ----------------------------------------------------------------------*/
void uart_write_c(char c) {
    volatile uint32_t flagregister = UART_BASE + 0x018;
    while (*(uint32_t *)flagregister & (1 << 5));

    *(volatile uint32_t *)UART_BASE = c;
}

/*----------------------------------------------------------------------
 * uart_read_char - reads a char from uart                              
 * Input: 
 *                                                                
 * Output: 
 *  char    -   character read                                                             
 ----------------------------------------------------------------------*/
char uart_read_c(void) {
    volatile uint32_t flagregister = UART_BASE + 0x18;
    while (*(uint32_t *)flagregister & (1 << 4));

    return *(volatile uint32_t *)UART_BASE & 0xFF;
}

/*----------------------------------------------------------------------
 * u_init - initializes uart connection
 * Inputs:
 * 
 * Outputs:
 *                                  
 ----------------------------------------------------------------------*/
void u_init(void) {
    *(volatile uint32_t *)(XOSC_REG) = (0xaa0 << 4); // Setting XOSC Freq to 1-15 MHz
    *(volatile uint32_t *)(XOSC_REG + 0xc) = 47; // Startup delay
    *(volatile uint32_t *)(XOSC_SET) = 0x00fab000; // Enable password
    while(!(*(volatile uint32_t *)(XOSC_REG + 0x4) & (1 << 12))); // Waiting for XOSC to be enabled
    while(!(*(volatile uint32_t *)(XOSC_REG + 0x4) & (1 << 31))); // Waiting for XOSC to stabilise

    *(volatile uint32_t *)(CLOCK + 0x30) = 0x2; // Setting system reference clock to XOSC
    *(volatile uint32_t *)(CLOCK + 0x3c) = 0x0; // Setting system clock to reference clock

    *(volatile uint32_t *)(RESET_CLR) = (1 << 5); // Clearing reset on I/O bank 0

    while (!(*(volatile uint32_t *)(RESET_DONE) & (1 << 5)));

    *(volatile uint32_t *)(RESET_SET) = (1 << UART_RST_BIT); // Resetting the UART
    *(volatile uint32_t *)(RESET_CLR) = (1 << UART_RST_BIT); // Bringing the UART out of reset

    // FIXME: Figure out why the C code is hanging at RESET_DONE
    // while (!((*(volatile uint32_t *)(RESET_DONE)) & (1 << UART_RST_BIT))); // Waiting for reset to complete

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
}

/*----------------------------------------------------------------------
 * uart_write - writes to uart    
 * Input:
 *  content -   buffer to write
 * 
 * Output:
 *                                        
 ----------------------------------------------------------------------*/
void uart_write(char * content) {
    for (; *content; content++) {
        if (*content == '\n') {
            uart_write_c('\r');
        }
        uart_write_c(*content);
    }
}

/*----------------------------------------------------------------------
 * uart_write_n - write n chars to uart
 * Input:
 *  content -   buffer to write
 *  size    -   length of buffer to write     
 * Output:
 *                             
 ----------------------------------------------------------------------*/
void uart_write_n(char * content, int size) {
    for (int i = 0; *content && (i < size); i++, content++) {
        if (*content == '\n') {
            uart_write_c('\r');
        }
        uart_write_c(*content);
    } 
}

/*----------------------------------------------------------------------
 * uart_write_hex - writes an integer's hex representation to uart     
 * Input:
 *  number  -   number to write
 * 
 * Output:
 *   
 ----------------------------------------------------------------------*/
void uart_write_hex(uint32_t number) {
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
    uart_write(num);
}

/*----------------------------------------------------------------------
 * uart_read - reads from uart into a buffer 
 * Input:
 *  buffer  -   buffer to read into
 *  size    -   max size of buffer
 * 
 * Output:
 *                            
 ----------------------------------------------------------------------*/
void uart_read(char * buffer, int size) {
    for (int i = 0; i < size; i++) {
        char c = uart_read_c();
        uart_write_c(c); // echo
        if (c == '\r') { // clearing \r\n (ew)
            buffer[i] = 0;
            // uart_read_c();
            uart_write_c('\n');
            return;
        }
        buffer[i] = c;
    }
}

/*----------------------------------------------------------------------
 * uart_is_readable - checks if uart rx buffer has something 
 * Input:
 *  
 * Output:
 *  bool    -   true if rx buffer has content, false otherwise           
 ----------------------------------------------------------------------*/
bool uart_is_recieving(void) {

}

#endif