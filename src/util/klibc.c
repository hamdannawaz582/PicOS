/* klibc.c - memcpy, memset */

#include <util/klibc.h>

void memcpy(void *dest, const void *src, size_t n) {
    char *d = dest;
    const char *s = src;

    for (size_t i = 0; i < n; i++, d++, s++) {
        *d = *s;
    }
}

void memset(void *dest, unsigned char c, size_t n) {
    char *d = dest;

    for (size_t i = 0; i < n; i++, d++) {
        *d = c;
    }
}