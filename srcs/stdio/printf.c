#include <stdio.h>

int printf(const char *format, ...) {
	va_list l;
	va_start(l, format);
	int r = vprintf(format, l);
	va_end(l);
	return r;
}
