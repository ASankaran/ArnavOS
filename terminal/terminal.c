#include "terminal.h"
#include "../devices/screen/screen.h"

unsigned char terminal_buffer[256] = { 0 };
int buffer_position = 0;

void add_char_to_terminal(unsigned char c) {
	kernel_print_char(c);
	terminal_buffer[buffer_position++] = c;
}

void add_newline_to_terminal(void) {
	kernel_print_newline();
}

void add_backspace_to_terminal(void) {
	kernel_print_backspace();
	terminal_buffer[--buffer_position] = 0;
}