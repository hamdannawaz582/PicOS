#include <driver/tty.h>
#include <board/loader.h>
#include "util/klibc.h"
#include <kernel/alloc.h>

extern int main(void);
extern void clock_init(void);
extern void run_all_tests(void);

void kinit() {
   clock_init();
   tty_init();
   printk(RESET_BACKGROUND CLEAR_SCREEN);
   KERNEL_PRINT("PicOS Booting...");
   KERNEL_PRINT("Clock Initialized");
   KERNEL_PRINT("TTY Initialized");
   KERNEL_PRINT("Kernel Heap starts at %x", (uint32_t)&__kheap_start);
   KERNEL_PRINT("Size of kheap block is %d bytes", sizeof(mem_block));
   KERNEL_PRINT("Running Tests...\n");
   run_all_tests();
   KERNEL_PRINT("Tests Completed");
   KERNEL_PRINT("Kernel Initialized");

   KERNEL_PRINT("Loading Kernel Proc");
   load_kernel((void *)main);
}