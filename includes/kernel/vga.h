#ifndef VGA_H
# define VGA_H

# include <stddef.h>
# include <stdint.h>

#define VGA_MEMORY	((uint16_t*)0xB8000)
#define VGA_WIDTH	((size_t)80)
#define VGA_HEIGHT	((size_t)25)
#define VGA_BUFSIZE	(VGA_WIDTH * VGA_HEIGHT)

/* Hardware text mode color constants. */
typedef enum e_vga_color {
	VGA_COLOR_BLACK,
	VGA_COLOR_BLUE,
	VGA_COLOR_GREEN,
	VGA_COLOR_CYAN,
	VGA_COLOR_RED,
	VGA_COLOR_MAGENTA,
	VGA_COLOR_BROWN,
	VGA_COLOR_LIGHT_GREY,
	VGA_COLOR_DARK_GREY,
	VGA_COLOR_LIGHT_BLUE,
	VGA_COLOR_LIGHT_GREEN,
	VGA_COLOR_LIGHT_CYAN,
	VGA_COLOR_LIGHT_RED,
	VGA_COLOR_LIGHT_MAGENTA,
	VGA_COLOR_LIGHT_BROWN,
	VGA_COLOR_WHITE
}	t_vga_color;

typedef uint8_t t_vga_entry_color;
typedef uint16_t t_vga_entry;

inline t_vga_entry_color vga_entry_color(t_vga_color fg, t_vga_color bg) {
	return fg | bg << 4;
}

inline t_vga_entry vga_entry(unsigned char c, t_vga_entry_color color) {
	return c | (t_vga_entry) color << 8;
}

inline void vga_put(char c, t_vga_entry_color color, size_t x, size_t y) {
	VGA_MEMORY[y * VGA_WIDTH + x] = vga_entry(c, color);
}

#endif
