#include "screen.h"

unsigned int current_loc = 0;
char *vidptr = (char*)0xb8000;

unsigned int cursor_row = 0;
unsigned int cursor_col = 0;

void kernel_print_string(const char *str) {
	unsigned int i = 0;
	while (str[i] != '\0') {
		vidptr[current_loc++] = str[i++];
		vidptr[current_loc++] = 0x07;
	}
	kernel_update_cursor();
}

void kernel_print_char(unsigned char c) {
	vidptr[current_loc++] = c;
	vidptr[current_loc++] = 0x07;
	kernel_update_cursor();
}

void kernel_print_newline(void) {
	unsigned int line_size = BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE;
	current_loc = current_loc + (line_size - current_loc % (line_size));
	kernel_update_cursor();
}

void kernel_print_backspace(void) {
	vidptr[--current_loc] = 0x07;
	vidptr[--current_loc] = ' ';
	kernel_update_cursor();
}

//Currently prints numbers in reverse.
void kernel_print_integer(int n) {
	unsigned char integer_map[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

	if (n < 0) {
		kernel_print_char('-');
		n *= -1;
	}
	if (n < 10) {
		kernel_print_char(integer_map[n]);
	} else {
		kernel_print_char(integer_map[n % 10]);
		kernel_print_integer(n / 10);
	}
}

void kernel_clear_screen(void) {
	unsigned int i = 0;
	while (i < SCREENSIZE) {
		vidptr[i++] = ' ';
		vidptr[i++] = 0x07;
	}
	kernel_move_cursor(0, 0);
}

static inline void kernel_outb(unsigned short port, unsigned char value) {
	asm volatile ( "outb %0, %1" : : "a"(value), "Nd"(port) );
}

void kernel_move_cursor(int row, int col) {
	cursor_row = row;
	cursor_col = col;

    unsigned short position = (row*80) + col;

    kernel_outb(0x3D4, 0x0F);
    kernel_outb(0x3D5, (unsigned char)(position&0xFF));

    kernel_outb(0x3D4, 0x0E);
    kernel_outb(0x3D5, (unsigned char )((position>>8)&0xFF));
}

void kernel_update_cursor(void) {
	unsigned short position = current_loc / 2;

    kernel_outb(0x3D4, 0x0F);
    kernel_outb(0x3D5, (unsigned char)(position&0xFF));

    kernel_outb(0x3D4, 0x0E);
    kernel_outb(0x3D5, (unsigned char )((position>>8)&0xFF));
}