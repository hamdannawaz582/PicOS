/* init.c - clock_init */

#include <stdint.h>

#define XOSC_REG 0x40024000
#define XOSC_SET XOSC_REG + 0x2000
#define CLOCK 0x40008000

void clock_init(void) {
    *(volatile uint32_t *)(XOSC_REG) = (0xaa0 << 4); // Setting XOSC Freq to 1-15 MHz
    *(volatile uint32_t *)(XOSC_REG + 0xc) = 47; // Startup delay
    *(volatile uint32_t *)(XOSC_SET) = 0x00fab000; // Enable password
    while(!(*(volatile uint32_t *)(XOSC_REG + 0x4) & (1 << 12))); // Waiting for XOSC to be enabled
    while(!(*(volatile uint32_t *)(XOSC_REG + 0x4) & (1 << 31))); // Waiting for XOSC to stabilise

    *(volatile uint32_t *)(CLOCK + 0x30) = 0x2; // Setting system reference clock to XOSC
    *(volatile uint32_t *)(CLOCK + 0x3c) = 0x0; // Setting system clock to reference clock
}