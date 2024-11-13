#include "utils.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*p;
	size_t			i;

	p = b;
	i = 0;
	while (i < len)
	{
		*(p + i) = c;
		i++;
	}
	return (b);
}
