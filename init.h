/* init.h - init */

/* Note: This will be replaced by an actual process once file transfers
*        are functional
*/
#ifndef INIT_H
#define INIT_H


#include "fs.h"
#include "uart.h"
#include "klibc.h"

void getline(char * buffer, size_t size) {
    char c;
    int index = 0;
    while (c = uart_read_c()) {
        uart_write_c(c);
        // Return at the end of a line
        if (c == 13 || c == EOF) {
            buffer[index] = 0;
            return;
        }

        // Return once size is full
        if (index == size - 1) {
            buffer[index] = 0;
            return;
        }

        buffer[index++] = c;
    }
}

void init(void) {
    size_t COMMANDSIZE = 256;
    char * commandbuffer = (char *)kmalloc(COMMANDSIZE*sizeof(char));

    while (1) {
        uart_write("$ ");
        uart_read(commandbuffer, COMMANDSIZE);
        char * tok = strtok(commandbuffer, " \n");
        while (tok != NULL) {
            uart_write(tok);
            uart_write("\n");
            
            if (strcmp(tok, "exit") == 0) {
                uart_write("Shutting down...\n");
                fs_close();
                __asm volatile (
                    "mov r0, #3\n"
                    "svc #0\n"
                );
            }
            tok = strtok(NULL, " \n");
        }
    }
}

#endif