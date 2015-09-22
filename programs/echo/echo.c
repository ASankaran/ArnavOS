#include "../../devices/screen/screen.h"

void start_echo_program(unsigned char input_args[]) {
	kernel_print_string(input_args);
	kernel_print_newline();
}