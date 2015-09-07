#define BYTES_FOR_EACH_ELEMENT 2
#define COLUMNS_IN_LINE 80
#define LINES 25
#define SCREENSIZE BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE * LINES

void print_string(const char *str);
void print_char(unsigned char c);
void print_newline(void);
void print_backspace(void);
void clear_screen(void);