#define KEYBOARD_STATUS_PORT 0x64
#define KEYBOARD_DATA_PORT 0x60
#define KERNEL_CODE_SEGMENT_OFFSET 0x08
#define INTERRUPT_GATE 0x8e
#define IDT_SIZE 256

#define ENTER_KEY_CODE 0x1C
#define CAPS_LOCK_KEY_CODE 0x3A
#define BACKSPACE_KEY_CODE 0x0E

extern unsigned char keyboard_map[128];
extern void keyboard_handler(void);
extern char read_port(unsigned short port);
extern void write_port(unsigned short port, unsigned char data);
extern void load_idt(unsigned long *idt_ptr);

void idt_init(void);
void keyboard_init(void);
void keyboard_handler_main(void);