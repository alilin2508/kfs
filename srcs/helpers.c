#include "helpers.h"

size_t 	strlen(const char* str)
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

int	strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);

}

void	*memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*cdst;
	const unsigned char	*csrc;

	i = 0;
	cdst = dst;
	csrc = src;
	if (!dst && !src)
		return (NULL);
	while (i < n)
	{
		cdst[i] = csrc[i];
		i++;
	}
	return (dst);
}
