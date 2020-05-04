#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "../include/kernel/tty.h"
#include "../arch/i368/tty.c"
 
void kernel_main(void) 
{
	kterm_init();
	kterm_writestring("Hello, kernel World!\n");
}
