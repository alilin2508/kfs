#ifndef TTY_H
# define TTY_H

# include <vga.h>

typedef struct s_tty {
	t_vga_entry_color color;
	size_t column;
	size_t row;
}	t_tty;

extern t_tty g_term;

void tty_clear();

void tty_init(t_vga_entry_color color);

void tty_putc(char c);

void tty_puts(const char *s);

void tty_setcolor(t_vga_entry_color color);

void tty_write(const char *data, size_t size);

#endif
