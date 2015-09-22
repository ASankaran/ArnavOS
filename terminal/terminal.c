#include "terminal.h"
#include "../devices/screen/screen.h"

#include "../programs/programs.h"

unsigned char terminal_buffer[TERMINAL_BUFFER_SIZE] = { 0 };
int buffer_position = 0;

void display_terminal_login_message(void) {
	const char *str = "Welcome to ArnavOS.";
	kernel_print_string(str);
	kernel_print_newline();
	kernel_print_string(TERMINAL_INPUT_PROMPT);
}

void add_char_to_terminal(unsigned char c) {
	kernel_print_char(c);
	terminal_buffer[buffer_position++] = c;
}

void add_newline_to_terminal(void) {
	kernel_print_newline();
	programs_run(terminal_buffer);
	while (buffer_position > 0) {
		terminal_buffer[--buffer_position] = 0;
	}
	kernel_print_string(TERMINAL_INPUT_PROMPT);
}

void add_backspace_to_terminal(void) {
	if (buffer_position - 1 < 0) {
		return;
	}
	kernel_print_backspace();
	terminal_buffer[--buffer_position] = 0;
}