#include <string.h>
#include <tty.h>

t_tty g_term;

static void inc_row() {
	g_term.column = 0;
	++g_term.row;
}

void tty_clear() {
	t_vga_entry c = vga_entry(' ', g_term.color);
	for (size_t i = 0; i < VGA_BUFSIZE; ++i)
		VGA_MEMORY[i] = c;
	g_term.column = 0;
	g_term.row = 0;
}

void tty_init(t_vga_entry_color color) {
	tty_setcolor(color);
	tty_clear();
}

void tty_putc(char c) {
	if (c == '\n')
		inc_row();
	else {
		vga_put(c, g_term.color, g_term.column, g_term.row);
		if (++g_term.column == VGA_WIDTH)
			inc_row();
	}
	if (g_term.row == VGA_HEIGHT)
		tty_clear();
}

void tty_puts(const char *s) {
	tty_write(s, strlen(s));
}

void tty_setcolor(t_vga_entry_color color) {
	g_term.color = color;
}

void tty_write(const char *data, size_t size) {
	for (size_t i = 0; i < size; ++i)
		tty_putc(data[i]);
}
