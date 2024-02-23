#include <_printf.h>

int vprintf(const char *format, va_list ap) {
	return __parse_format(format, ap);
}
