#include <_printf.h>

int vsnprintf(char *str, size_t n, const char *format, va_list ap) {
	return __parse_format_nstr(str, n, format, ap);
}
