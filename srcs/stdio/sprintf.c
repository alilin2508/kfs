#include <stdarg.h>
#include <stdio.h>

int sprintf(char *str, const char *format, ...) {
	va_list l;
	va_start(l, format);
	int r = vsprintf(str, format, l);
	va_end(l);
	return r;
}
