#include "screen.h"

unsigned int current_loc = 0;
char *vidptr = (char*)0xb8000;

void print_string(const char *str) {
	unsigned int i = 0;
	while (str[i] != '\0') {
		vidptr[current_loc++] = str[i++];
		vidptr[current_loc++] = 0x07;
	}
}

void print_char(unsigned char c) {
	vidptr[current_loc++] = c;
	vidptr[current_loc++] = 0x07;
}

void print_newline(void) {
	unsigned int line_size = BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE;
	current_loc = current_loc + (line_size - current_loc % (line_size));
}

void print_backspace(void) {
	vidptr[--current_loc] = 0x07;
	vidptr[--current_loc] = ' ';
}

void clear_screen(void) {
	unsigned int i = 0;
	while (i < SCREENSIZE) {
		vidptr[i++] = ' ';
		vidptr[i++] = 0x07;
	}
}