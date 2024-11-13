#include "utils.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*str;

	if (count != 0 && size > (SIZE_MAX / count))
		return (NULL);
	str = malloc(size * count);
	if (!str)
		return (NULL);
	ft_bzero(str, (count * size));
	return (str);
}
