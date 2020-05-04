#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <kernel/tty.h>

void kernel_main(void) 
{
	kterm_init();
	kterm_writestring("Hello, kernel World!\n");
}
