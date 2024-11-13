#include "utils.h"

int	ft_isbashchars(int c)
{
	if (c != 124 && c != 60 && c != 62 && c != 39 && c != 34)
		return (1);
	return (0);
}

int	ft_isprint(int c)
{
	if ((c > 32 && c <= 126) && ft_isbashchars(c))
		return (1);
	return (0);
}
