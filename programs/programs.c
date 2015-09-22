#include "programs.h"

#include "../devices/screen/screen.h"

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

//Should be moved to lib once string methods are set up
int cmpstr(unsigned char str1[], unsigned char str2[]) {
	int i = 0;
	if (strlen(str1) != strlen(str2)) {
		return 0;
	}
	while (str1[i] != '\0') {
		if (str1[i] != str2[i]) {
			return 0;
		}
		i++;
	}
	return 1;
}

int strlen(unsigned char str[]) {
	int i = 0;
	while (str[i] != '\0') {
		i++;
	}
	return i;
}