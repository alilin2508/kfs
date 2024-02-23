#include <_printf.h>
#include <sys/types.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

static inline void pf_putchar(t_format *f, const char c) {
	if (f->size == EOF)
		return;
	if (f->output_str) {
		if (f->has_max_size && (size_t)f->size == f->max_size)
			return;
		f->output_str[f->size] = c;
	} else if (putchar(c) == EOF) {
		f->size = EOF;
		return;
	}
	++f->size;
}

static inline void pf_putstr(t_format *f, const char *s) {
	while (*s)
		pf_putchar(f, *s++);
}

static inline void pf_putpadding(t_format *f) {
	while (f->width--)
		pf_putchar(f, f->flags & FLAG_ZERO ? '0' : ' ');
}

static inline void pf_padding_prefix(t_format *f) {
	if (!(f->flags & FLAG_MINUS))
		pf_putpadding(f);
}

static inline void pf_padding_suffix(t_format *f) {
	if (f->flags & FLAG_MINUS)
		pf_putpadding(f);
}

static inline int max_int(int a, int b) {
	return a > b ? a : b;
}

static inline int min_int(int a, int b) {
	return a < b ? a : b;
}

// Avoid undefined reference to `__udivmoddi4' error with GCC
static inline void divmod(t_ull n, t_ull d, t_ull *q, t_ull *r) {
	t_ull qn = 0, qd = 1;
	while ((t_ll)d >= 0 && d < n) {
		d <<= 1;
		qd <<= 1;
	}
	while (qd) {
		if (n >= d) {
			n -= d;
			qn += qd;
		}
		d >>= 1;
		qd >>= 1;
	}
	*q = qn;
	*r = n;
}

static char *num_to_string(t_ull n, int base) {
	static char	buf[PF_CONVERT_BUFSIZE];
	const char	*b16 = "0123456789abcdef";
	char		*d;

	d = buf + sizeof(buf);
	*--d = '\0';
	if (!n)
		*--d = '0';
	while (n) {
		t_ull r;
		divmod(n, base, &n, &r);
		*--d = b16[r];
	}
	return d;
}

static const char *parse_int(int *i, const char *s) {
	int n = 0;
	while (isdigit(*s))
		n = 10 * n + *s++ - '0';
	*i = n;
	return s;
}

static inline const char *parse_flags(t_format *f, const char *s) {
	const char *flags = "#0- +";
	char *i;
	f->flags = 0;
	while ((i = strchr(flags, *s)))
		f->flags |= 1 << (i - flags), ++s;
	return s;
}

static inline const char *parse_width(t_format *f, const char *s) {
	f->width = 0;
	if (*s == '*') {
		f->width = va_arg(f->args, int);
		++s;
		if (f->width < 0) {
			f->width = -f->width;
			f->flags |= FLAG_MINUS;
		}
	}
	else
		s = parse_int(&f->width, s);
	return s;
}

static inline const char *parse_precision(t_format *f, const char *s) {
	if (*s == '.') {
		if (*(++s) == '*') {
			f->precision = va_arg(f->args, int);
			++s;
			if (f->precision < 0)
				f->precision = -1;
		}
		else
			s = parse_int(&f->precision, s);
	} else
		f->precision = -1;
	return s;
}

static inline const char *parse_modifier(t_format *f, const char *s) {
	static const char *modifiers[] = { "hh", "h", "ll", "l", "j", "z", "t" };
	f->modifier = 0;
	for (size_t i = 0; i < sizeof(modifiers) / sizeof(*modifiers); ++i)
		if (!strncmp(s, modifiers[i], strlen(modifiers[i]))) {
			f->modifier = 1 << i;
			return s + strlen(modifiers[i]);
		}
	return s;
}

static inline const char *parse_directives(t_format *f, const char *s) {
	s = parse_flags(f, s);
	s = parse_width(f, s);
	s = parse_precision(f, s);
	s = parse_modifier(f, s);
	return s;
}

static inline t_ll extract_signed_numeric(t_modifier m, va_list *l) {
	t_ll n;
	if (m & MODIFIER_LL)
		n = va_arg(*l, t_ll);
	else if (m & MODIFIER_L)
		n = va_arg(*l, long);
	else if (m & MODIFIER_HH)
		n = (char)va_arg(*l, int);
	else if (m & MODIFIER_H)
		n = (short)va_arg(*l, int);
	else if (m & MODIFIER_J)
		n = va_arg(*l, intmax_t);
	else if (m & MODIFIER_Z)
		n = va_arg(*l, ssize_t);
	else if (m & MODIFIER_T)
		n = va_arg(*l, ptrdiff_t);
	else
		n = va_arg(*l, int);
	return n;
}

static inline void print_sign(t_format *f, t_ll n) {
	if (n < 0)
		pf_putchar(f, '-');
	else if (f->flags & FLAG_PLUS)
		pf_putchar(f, '+');
	else if (f->flags & FLAG_SPACE)
		pf_putchar(f, ' ');
}

static inline void print_signed_numeric(t_format *f) {
	t_ll n = extract_signed_numeric(f->modifier, &f->args);
	char *b = num_to_string(n < 0 ? -n : n, 10);
	int length = strlen(b);
	int sign = n < 0 || (f->flags & (FLAG_PLUS | FLAG_SPACE));
	int unset_precision = f->precision < 0;
	f->precision = max_int(f->precision - length, 0);
	f->width = max_int(f->width - f->precision - length - sign, 0);
	if (f->flags & FLAG_ZERO)
		print_sign(f, n);
	pf_padding_prefix(f);
	if (!(f->flags & FLAG_ZERO))
		print_sign(f, n);
	for (int i = 0; i < f->precision; ++i)
		pf_putchar(f, '0');
	if (f->precision || n || unset_precision)
		pf_putstr(f, b);
	pf_padding_suffix(f);
}

static inline t_ull extract_unsigned_numeric(t_modifier m, va_list *l) {
	t_ull n;
	if (m & MODIFIER_LL)
		n = va_arg(*l, t_ull);
	else if (m & MODIFIER_L)
		n = va_arg(*l, unsigned long);
	else if (m & MODIFIER_HH)
		n = (unsigned char)va_arg(*l, unsigned int);
	else if (m & MODIFIER_H)
		n = (unsigned short)va_arg(*l, unsigned int);
	else if (m & MODIFIER_J)
		n = va_arg(*l, uintmax_t);
	else if (m & MODIFIER_Z)
		n = va_arg(*l, size_t);
	else if (m & MODIFIER_T)
		n = va_arg(*l, ptrdiff_t);
	else
		n = va_arg(*l, unsigned int);
	return n;
}

static inline const char *get_hash(const char c) {
	if (c == 'o')
		return "0";
	else if (c == 'x')
		return "0x";
	else if (c == 'X')
		return "0X";
	return NULL;
}

static inline void str_to_upper(char *s) {
	while (*s)
		*s = toupper(*s), ++s;
}

static inline void print_unsigned_numeric(t_format *f, const char c, t_ull n) {
	const int base = tolower(c) == 'x' ? 16 : (c == 'o' ? 8 : 10);
	const char *hash = f->flags & FLAG_HASH ? get_hash(c) : NULL;
	int hash_length = hash ? strlen(hash) : 0;
	char *b = num_to_string(n, base);
	int length = strlen(b);
	if (c == 'X')
		str_to_upper(b);
	int unset_precision = f->precision < 0;
	f->precision = max_int(f->precision - length - (hash_length * (c == 'o')), 0);
	f->width = max_int(f->width - f->precision - length - hash_length, 0);
	pf_padding_prefix(f);
	if (hash && (f->precision || n))
		pf_putstr(f, hash);
	for (int i = 0; i < f->precision; ++i)
		pf_putchar(f, '0');
	if (f->precision || n || unset_precision || (hash && c == 'o'))
		pf_putstr(f, b);
	pf_padding_suffix(f);
}

static inline void print_char(t_format *f) {
	unsigned char c = va_arg(f->args, int);
	f->width = max_int(f->width - 1, 0);
	pf_padding_prefix(f);
	pf_putchar(f, c);
	pf_padding_suffix(f);
}

static inline void print_str(t_format *f, const char *s) {
	if (!s)
		s = "(null)";
	int length = strlen(s);
	if (f->precision >= 0)
		length = min_int(length, f->precision);
	f->width = max_int(f->width - length, 0);
	pf_padding_prefix(f);
	while (length--)
		pf_putchar(f, *s++);
	pf_padding_suffix(f);
}

static inline void print_pointer(t_format *f) {
	f->modifier = MODIFIER_L;
	t_ull n = extract_unsigned_numeric(f->modifier, &f->args);
	if (!n) {
		print_str(f, "(nil)");
		return;
	}
	f->flags = FLAG_HASH;
	print_unsigned_numeric(f, 'x', n);
}

static inline void store_written(t_format *f) {
	const t_modifier m = f->modifier;
	if (m & MODIFIER_LL) {
		long long *n = va_arg(f->args, long long*);
		*n = f->size;
	} else if (m & MODIFIER_L) {
		long *n = va_arg(f->args, long*);
		*n = f->size;
	} else if (m & MODIFIER_HH) {
		char *n = va_arg(f->args, char*);
		*n = f->size;
	} else if (m & MODIFIER_H) {
		short *n = va_arg(f->args, short*);
		*n = f->size;
	} else if (m & MODIFIER_J) {
		intmax_t *n = va_arg(f->args, intmax_t*);
		*n = f->size;
	} else if (m & MODIFIER_Z) {
		ssize_t *n = va_arg(f->args, ssize_t*);
		*n = f->size;
	} else if (m & MODIFIER_T) {
		ptrdiff_t *n = va_arg(f->args, ptrdiff_t*);
		*n = f->size;
	} else {
		int *n = va_arg(f->args, int*);
		*n = f->size;
	}
}

static int __parse_format_internal(t_format *f, const char *s) {
	while (*s && f->size != EOF)
		if (*s != '%' || *++s == '%')
			pf_putchar(f, *s++);
		else {
			s = parse_directives(f, s);
			if ((f->flags & FLAG_MINUS) || f->precision >= 0)
				f->flags &= ~FLAG_ZERO;
			if (f->flags & FLAG_PLUS)
				f->flags &= ~FLAG_SPACE;
			if (strchr("di", *s))
				print_signed_numeric(f);
			else if (strchr("ouxX", *s))
				print_unsigned_numeric(f, *s, extract_unsigned_numeric(f->modifier, &f->args));
			else if (*s == 'c')
				print_char(f);
			else if (*s == 's')
				print_str(f, va_arg(f->args, char*));
			else if (*s == 'p')
				print_pointer(f);
			else if (*s == 'n')
				store_written(f);
			else
				continue;
			++s;
		}
	return f->size;
}

int __parse_format(const char *s, va_list l) {
	t_format f = { 0 };
	va_copy(f.args, l);
	return __parse_format_internal(&f, s);
}

int __parse_format_str(char *dst, const char *s, va_list l) {
	t_format f = { 0 };
	va_copy(f.args, l);
	f.output_str = dst;
	int size = __parse_format_internal(&f, s);
	if (size != EOF)
		dst[size] = '\0';
	return size;
}

int __parse_format_nstr(char *dst, size_t n, const char *s, va_list l) {
	t_format f = { 0 };
	va_copy(f.args, l);
	f.output_str = dst;
	f.has_max_size = 1;
	f.max_size = n;
	int size = __parse_format_internal(&f, s);
	if (size != EOF && (size_t)size < f.max_size)
		dst[size] = '\0';
	return size;
}
