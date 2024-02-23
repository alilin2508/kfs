#include <stdarg.h>
#include <stdio.h>

int snprintf(char *str, size_t n, const char *format, ...) {
	va_list l;
	va_start(l, format);
	int r = vsnprintf(str, n, format, l);
	va_end(l);
	return r;
}
