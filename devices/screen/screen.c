#include "screen.h"

unsigned int current_loc = 0;
char *vidptr = (char*)0xb8000;

unsigned int cursor_row = 0;
unsigned int cursor_col = 0;

void print_string(const char *str) {
	unsigned int i = 0;
	while (str[i] != '\0') {
		vidptr[current_loc++] = str[i++];
		vidptr[current_loc++] = 0x07;
	}
	update_cursor();
}

void print_char(unsigned char c) {
	vidptr[current_loc++] = c;
	vidptr[current_loc++] = 0x07;
	update_cursor();
}

void print_newline(void) {
	unsigned int line_size = BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE;
	current_loc = current_loc + (line_size - current_loc % (line_size));
	update_cursor();
}

void print_backspace(void) {
	vidptr[--current_loc] = 0x07;
	vidptr[--current_loc] = ' ';
	update_cursor();
}

void clear_screen(void) {
	unsigned int i = 0;
	while (i < SCREENSIZE) {
		vidptr[i++] = ' ';
		vidptr[i++] = 0x07;
	}
	move_cursor(0, 0);
}

static inline void outb(unsigned short port, unsigned char value) {
	asm volatile ( "outb %0, %1" : : "a"(value), "Nd"(port) );
}

void move_cursor(int row, int col) {
	cursor_row = row;
	cursor_col = col;

    unsigned short position = (row*80) + col;

    outb(0x3D4, 0x0F);
    outb(0x3D5, (unsigned char)(position&0xFF));

    outb(0x3D4, 0x0E);
    outb(0x3D5, (unsigned char )((position>>8)&0xFF));
}

void update_cursor(void) {
	unsigned short position = current_loc / 2;

    outb(0x3D4, 0x0F);
    outb(0x3D5, (unsigned char)(position&0xFF));

    outb(0x3D4, 0x0E);
    outb(0x3D5, (unsigned char )((position>>8)&0xFF));
}