#ifndef _PRINTF_H
# define _PRINTF_H

# include <stdarg.h>
# include <stddef.h>
# include <stdint.h>

# define PF_CONVERT_BUFSIZE 64

typedef long long			t_ll;
typedef unsigned long long	t_ull;

typedef enum e_flags {
	FLAG_HASH = 0x1,
	FLAG_ZERO = 0x2,
	FLAG_MINUS = 0x4,
	FLAG_SPACE = 0x8,
	FLAG_PLUS = 0x10
}	t_flags;

typedef enum e_modifier {
	MODIFIER_HH = 0x1,
	MODIFIER_H = 0x2,
	MODIFIER_LL = 0x4,
	MODIFIER_L = 0x8,
	MODIFIER_J = 0x10,
	MODIFIER_Z = 0x20,
	MODIFIER_T = 0x40
}	t_modifier;

typedef struct s_format {
	va_list		args;

	// Format directives
	t_flags		flags;
	int			width;
	int			precision;
	t_modifier	modifier;

	// Output control
	char		*output_str;
	int			has_max_size;
	size_t		max_size;
	int			size;
}	t_format;

int	__parse_format(const char *s, va_list l);

int	__parse_format_str(char *dst, const char *s, va_list l);

int	__parse_format_nstr(char *dst, size_t n, const char *s, va_list l);

#endif
