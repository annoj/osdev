#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "../../include/kernel/tty.h"

#include "vga.h"

size_t strlen(const char* str) 
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}
 
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
 
size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;
 
void kterm_init(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}
 
void _kterm_setcolor(uint8_t color) 
{
	terminal_color = color;
}
 
void _kterm_putenryat(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void _kterm_scroll() {
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const char c = terminal_buffer[(y + 1) * VGA_WIDTH + x];
			_kterm_putenryat(c, terminal_color, x, y);
		}
	}
}

void _kterm_nextrow() {
	if (terminal_row == VGA_HEIGHT - 1)
		_kterm_scroll();
	else
		terminal_row++;
}
 
void kterm_putchar(char c) 
{
	// Handle newlines
	if (c == '\n') {
		_kterm_nextrow();
		terminal_column = 0;
		return;
	}

	// Put char to terminal buffer
	_kterm_putenryat(c, terminal_color, terminal_column, terminal_row);

	// handle terminal boundaries (max col and max row)
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		_kterm_nextrow();
	}
}
 
void kterm_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		kterm_putchar(data[i]);
}
 
void kterm_writestring(const char* data) 
{
	kterm_write(data, strlen(data));
}
