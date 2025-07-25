#include <kernel/config.h>
#include <driver/tty.h>

int main(void) {
    while(1) {
        tty_puts("Hello World!\n");
    }
}