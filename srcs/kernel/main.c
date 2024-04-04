#include <stdint.h>
#include <string.h>
#include "gdt.h"

/* affichage par buffer vga géré par grub */
enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15
};
 
static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) 
{
	return fg | bg << 4;
}
 
static inline uint16_t vga_entry(unsigned char uc, uint8_t color) 
{
	return (uint16_t) uc | (uint16_t) color << 8;
}
 
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
 
uint8_t terminal_color;
uint16_t* terminal_buffer;
 
void terminal_initialize(void) 
{
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_MAGENTA, VGA_COLOR_WHITE);
	terminal_buffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void kernel_main(void) // GRUB lance le kernel en protected mode (protection de la mémoire par la segmentation) contrairement au real mode (tous les programmes peuvent accéder à tous les espaces mémoires)
{
	terminal_initialize();
	init_gdt();

    //dans la table ascii 52 = '4'	
	terminal_buffer[0] = vga_entry((char)strlen("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"), terminal_color);
	//dans la table ascii ('z')122 - ('H')72 = ('2')50
	terminal_buffer[1] = vga_entry((char)strncmp("z", "H", 1), terminal_color);
	terminal_buffer[80] = vga_entry('W', vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_MAGENTA));
	terminal_buffer[81] = vga_entry('e', vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLUE));
	terminal_buffer[82] = vga_entry('l', vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_LIGHT_CYAN));
	terminal_buffer[83] = vga_entry('c', vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_CYAN));
	terminal_buffer[84] = vga_entry('o', vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_LIGHT_GREEN));
	terminal_buffer[85] = vga_entry('m', vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_LIGHT_BROWN));
	terminal_buffer[86] = vga_entry('e', vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_LIGHT_RED));
	terminal_buffer[87] = vga_entry('!', vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_RED));
}
