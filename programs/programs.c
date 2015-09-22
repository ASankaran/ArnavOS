#include "programs.h"

#include "../lib/string/string.h"

#include "echo/echo.h"

void programs_run(unsigned char input[]) {
	unsigned char input_program[INPUT_BUFFER_SIZE] = { 0 };
	unsigned char input_args[INPUT_BUFFER_SIZE] = { 0 };
	int i = 0;
	while(input[i] != ' ' && input[i] != '\0') {
		input_program[i] = input[i];
		i++;
	}
	int j = 0;
	i++;
	while(input[i] != '\0') {
		input_args[j] = input[i];
		i++;
		j++;
	}

	if(cmpstr(input_program, "echo")) {
		start_echo_program(input_args);
	}
}