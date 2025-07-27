//
// Created by Hamdan Nawaz on 27/07/2025.
//

#ifndef PANIC_H
#define PANIC_H

#include <util/klibc.h>

#define PANIC(fmt, ...) \
    printk(RED_BACKGROUND CLEAR_SCREEN "PANIC" "\n\n" fmt, ##__VA_ARGS__); \
    while (1) { \
        };

#endif //PANIC_H
