#include "../devices/keyboard/keyboard.h"
#include "../devices/screen/screen.h"

void kernel_main(void) {
	const char *str = "ArnavOS with keyboard support.";
	clear_screen();
	print_string(str);
	print_newline();
	print_newline();

	idt_init();
	keyboard_init();

	while(1);
}