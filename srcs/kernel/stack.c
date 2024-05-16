#include <stdio.h>
#include <stack.h>
#include <tty.h>

void print_stack() {
	t_stackframe *sf;
	asm ("movl %%ebp,%0" : "=r"(sf) ::);
	// on parcourt la pile en itérant sur le registre ebp
	for(unsigned int frame = 0; sf && frame < MAX_STACK_FRAMES; ++frame) {
		printf("  #%d ", frame);
		t_vga_entry_color old_color = g_term.color;
		tty_setcolor(vga_entry_color(VGA_COLOR_LIGHT_CYAN, VGA_COLOR_BLACK));
		printf("0x%08x\n", sf->eip); // affiche l'adresse de retour de la fonction
		tty_setcolor(old_color);
		sf = sf->ebp;
	}
}
