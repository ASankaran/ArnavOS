#include "keyboard.h"
#include "keyboard_map.h"
#include "../screen/screen.h"
#include "../../terminal/terminal.h"

struct IDT_entry {
	unsigned short int lowerbits_offset;
	unsigned short int selector;
	unsigned char zero;
	unsigned char type_attr;
	unsigned short int higherbits_offset;
};

struct IDT_entry IDT[IDT_SIZE];

void idt_init(void) {
	unsigned long keyboard_address = (unsigned long)keyboard_handler;

	IDT[0x21].higherbits_offset = (keyboard_address & 0xffff0000) >> 16;
	IDT[0x21].selector = KERNEL_CODE_SEGMENT_OFFSET;
	IDT[0x21].lowerbits_offset = keyboard_address & 0xffff;
	IDT[0x21].type_attr = INTERRUPT_GATE;
	IDT[0x21].zero = 0;
	IDT[0x21].type_attr = INTERRUPT_GATE;
	

	write_port(0x20 , 0x11);
	write_port(0xA0 , 0x11);

	write_port(0x21 , 0x20);
	write_port(0xA1 , 0x28);

	write_port(0x21 , 0x00);
	write_port(0xA1 , 0x00);

	write_port(0x21 , 0x01);
	write_port(0xA1 , 0x01);

	write_port(0x21 , 0xff);
	write_port(0xA1 , 0xff);

	unsigned long idt_address = (unsigned long)IDT;

	unsigned long idt_ptr[2];
	idt_ptr[0] = (sizeof (struct IDT_entry) * IDT_SIZE) + ((idt_address & 0xffff) << 16);
	idt_ptr[1] = idt_address >> 16 ;

	load_idt(idt_ptr);
}

void keyboard_init(void) {
	write_port(0x21 , 0xFD);
}

unsigned int capslock_enabled = 0;
unsigned int shift_enabled = 0;

void keyboard_handler_main(void) {
	write_port(0x20, 0x20);

	unsigned char status = read_port(KEYBOARD_STATUS_PORT);

	if (status & 0x01) {
		int keycode = read_port(KEYBOARD_DATA_PORT);
		if (keycode < 0) {
			if (keycode * -1 == RIGHT_SHIFT_RELEASED_KEY_CODE || keycode * -1 == LEFT_SHIFT_RELEASED_KEY_CODE) {
				shift_enabled = 0;
			}
			return;
		}

		if (keycode == ENTER_KEY_CODE) {
			add_newline_to_terminal();
			return;
		}

		if (keycode == CAPS_LOCK_KEY_CODE) {
			if (capslock_enabled) {
				capslock_enabled = 0;
			} else {
				capslock_enabled = 1;
			}
			return;
		}

		if (keycode == BACKSPACE_KEY_CODE) {
			add_backspace_to_terminal();
			return;
		}

		if (keycode == LEFT_SHIFT_PRESSED_KEY_CODE || keycode == RIGHT_SHIFT_PRESSED_KEY_CODE) {
			shift_enabled = 1;
			return;
		}

		unsigned char ascii_key = keyboard_map[(unsigned char) keycode];

		if (capslock_enabled){
			if (ascii_key >= 97 && ascii_key <= 122) {
				add_char_to_terminal(ascii_key - 32);
				return;
			}
		}

		if (shift_enabled) {
			add_char_to_terminal(keyboard_map_shifted[(unsigned char) keycode]);
			return;
		}
		add_char_to_terminal(ascii_key);
	}
}