#include <vga.h>

void vga_fill(char c, t_vga_entry_color color) {
	for (size_t i = 0; i < VGA_WIDTH * VGA_HEIGHT; ++i)
		VGA_MEMORY[i] = vga_entry(c, color);
}

void vga_put(char c, t_vga_entry_color color, size_t x, size_t y) {
	VGA_MEMORY[y * VGA_WIDTH + x] = vga_entry(c, color);
}
