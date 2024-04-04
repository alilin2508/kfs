#include <gdt.h>
#include <stdio.h>
#include <tty.h>

void init_terminal() {
	tty_init(vga_entry_color(VGA_COLOR_LIGHT_MAGENTA, VGA_COLOR_WHITE));
	VGA_MEMORY[0] = vga_entry('W', vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_MAGENTA));
	VGA_MEMORY[1] = vga_entry('e', vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLUE));
	VGA_MEMORY[2] = vga_entry('l', vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_LIGHT_CYAN));
	VGA_MEMORY[3] = vga_entry('c', vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_CYAN));
	VGA_MEMORY[4] = vga_entry('o', vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_LIGHT_GREEN));
	VGA_MEMORY[5] = vga_entry('m', vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_LIGHT_BROWN));
	VGA_MEMORY[6] = vga_entry('e', vga_entry_color(VGA_COLOR_BLACK, VGA_COLOR_LIGHT_RED));
	VGA_MEMORY[7] = vga_entry('!', vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_RED));
	putchar('\n');
	printf("This is a test message with printf: %d %s\n", 42, "hello");
}

// GRUB lance le kernel en protected mode (protection de la mémoire par la segmentation) contrairement au real mode (tous les programmes peuvent accéder à tous les espaces mémoires)
void kernel_main() {
	init_terminal();
	init_gdt();
}
