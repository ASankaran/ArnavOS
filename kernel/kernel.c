#include "../devices/keyboard/keyboard.h"
#include "../devices/screen/screen.h"

void kernel_main(void) {
	const char *str = "ArnavOS with keyboard support.";
	kernel_clear_screen();
	kernel_print_string(str);
	kernel_print_newline();
	kernel_print_newline();

	idt_init();
	keyboard_init();

	while(1);
}