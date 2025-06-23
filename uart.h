#ifndef UART_H
#define UART_H

#include <hardware/uart.h>

#ifndef USE_UART1
    struct uart_inst * uart = uart0;
#else
    struct uart_inst * uart = uart1;
#endif

/*----------------------------------------------------------------------
 * u_init - initializes uart connection
 * Inputs:
 * 
 * Outputs:
 *                                  
 ----------------------------------------------------------------------*/
void u_init(void) {
    uart_init(uart, 115200);
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
            uart_putc(uart, '\r');
        }
        uart_putc(uart, *content);
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
            uart_putc(uart, '\r');
        }
        uart_putc(uart, *content);
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