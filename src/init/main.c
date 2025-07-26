#include <driver/tty.h>

#include "util/klibc.h"

extern int main(void);
extern void clock_init(void);
extern void run_all_tests(void);

void kinit() {
   clock_init();
   tty_init();
   printk(CLEAR_SCREEN);
   KERNEL_PRINT("PicOS Booting...");
   KERNEL_PRINT("Clock Initialized");
   KERNEL_PRINT("TTY Initialized");
   KERNEL_PRINT("Running Tests...\n");
   run_all_tests();
   KERNEL_PRINT("Tests Completed");
   KERNEL_PRINT("Kernel Initialized");
   main();
}