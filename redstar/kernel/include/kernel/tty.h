#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <stddef.h>

void kterm_init(void);
void kterm_putchar(char c);
void kterm_write(const char *data, size_t size);
void kterm_writestring(const char *s);

#endif
