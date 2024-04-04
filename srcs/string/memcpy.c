#include <stddef.h>

void *memcpy(void *dst, const void *src, size_t n)
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
