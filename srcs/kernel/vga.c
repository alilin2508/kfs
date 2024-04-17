#include <vga.h>

t_vga_entry_color vga_entry_color(t_vga_color fg, t_vga_color bg) {
	return fg | bg << 4;
}

t_vga_entry vga_entry(unsigned char c, t_vga_entry_color color) {
	return c | (t_vga_entry) color << 8;
}

void vga_put(char c, t_vga_entry_color color, size_t x, size_t y) {
	VGA_MEMORY[y * VGA_WIDTH + x] = vga_entry(c, color);
}
