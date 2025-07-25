#include <driver/tty.h>

extern int main(void);
extern void clock_init(void);

void kinit() {
   clock_init();
   tty_init();
   main();
}