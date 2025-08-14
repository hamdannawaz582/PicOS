#include <kernel/config.h>
#include "kernel/scheduler_test.h"
#include "kernel/allocator_test.h"
#include <stdint.h>

uint32_t tests = 0;
uint32_t passed = 0;

#define RUN_TEST(test, name) printk("[" YELLOW "TEST" RESET "]\t" "Testing " BRIGHT_YELLOW name RESET " "); \
    if (test() == true) { \
        printk(GREEN "PASSED\n" RESET); \
        passed++; \
    } else { \
        printk(RED "FAILED\n" RESET); \
    } \
    tests++;

#define TEST_CATEGORY(name) \
    if (tests != 0) { \
        printk("[" YELLOW "TEST" RESET "]\t" BRIGHT_YELLOW "Category Summary " RESET); \
        printk("%d/%d PASS\n\n", passed, tests); \
        tests = passed = 0; \
    } \
    printk("[" YELLOW "TEST" RESET "]\t" BRIGHT_YELLOW "Category Start " YELLOW name RESET "\n");




void run_all_tests(void) {
#ifdef TEST

    TEST_CATEGORY("Scheduler");
    RUN_TEST(test_scheduler_init, "scheduler_init");
    RUN_TEST(test_add_proc, "add_proc");
    TEST_CATEGORY("Allocator");
    RUN_TEST(test_allocator_init, "allocator_init");
    RUN_TEST(test_allocator_malloc, "allocator_add");
    RUN_TEST(test_allocator_free, "allocator_free");
    TEST_CATEGORY("Memory");

#endif
}

