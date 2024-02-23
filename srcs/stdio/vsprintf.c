#include <_printf.h>

int vsprintf(char *str, const char *format, va_list ap) {
	return __parse_format_str(str, format, ap);
}
