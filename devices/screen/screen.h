#define BYTES_FOR_EACH_ELEMENT 2
#define COLUMNS_IN_LINE 80
#define LINES 25
#define SCREENSIZE BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE * LINES

void kernel_print_string(const char *str);
void kernel_print_char(unsigned char c);
void kernel_print_newline(void);
void kernel_print_integer(int n);
void kernel_print_backspace(void);
void kernel_clear_screen(void);
void kernel_move_cursor(int row, int col);
void kernel_update_cursor(void);