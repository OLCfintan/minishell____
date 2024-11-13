#include "utils.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*s;
	unsigned char	*d;

	i = 0;
	s = (unsigned char *)src;
	d = dst;
	if (d == s)
		return (d);
	if (!dst && !src)
		return (NULL);
	while (i < n)
	{
		*(d + i) = *(s + i);
		i++;
	}
	return (dst);
}
