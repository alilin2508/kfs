#ifndef STDIO_H
# define STDIO_H

# include <stdarg.h>
# include <stddef.h>

# define EOF (-1)

int	printf(const char *format,
	...) __attribute__((format(printf,1,2),nonnull(1)));

int	putchar(int c);

int	puts(const char *s);

int	snprintf(char *str, size_t n, const char *format,
	...) __attribute__((format(printf,3,4),nonnull(3)));

int	sprintf(char *str, const char *format,
	...) __attribute__((format(printf,2,3),nonnull(2),nonnull(1)));

int	vprintf(const char *format,
	va_list ap) __attribute__((format(printf,1,0),nonnull(1)));

int	vsnprintf(char *str, size_t n, const char *format,
	va_list ap) __attribute__((format(printf,3,0),nonnull(3)));

int	vsprintf(char *str, const char *format,
	va_list ap) __attribute__((format(printf,2,0),nonnull(2),nonnull(1)));

#endif
