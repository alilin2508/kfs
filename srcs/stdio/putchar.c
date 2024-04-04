#include <stdio.h>
#include <tty.h>

int putchar(int ic) {
	tty_putc(ic);
	return ic;
}
