#include "../devices/keyboard/keyboard.h"
#include "../devices/screen/screen.h"
#include "../terminal/terminal.h"

void kernel_main(void) {
	kernel_clear_screen();
	display_terminal_login_message();

	idt_init();
	keyboard_init();

	while(1);
}