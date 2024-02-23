#ifndef STRING_H
# define STRING_H

# include <stddef.h>

char	*strchr(const char *s, int c);
size_t	strlen(const char* str);
int		strncmp(const char *s1, const char *s2, size_t n);

#endif

