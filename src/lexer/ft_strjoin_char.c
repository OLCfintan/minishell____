
#include "../../include/minishell.h"

char	*ft_strjoin_char(char *s1, char c)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + 2));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		str[j++] = s1[i++];
	str[j++] = c;
	str[j] = '\0';
	free(s1);
	return (str);
}
