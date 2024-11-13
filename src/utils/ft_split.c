
#include "../../include/minishell.h"

static size_t	ft_count_words(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static size_t	ft_word_len(char const *str, char c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (str[i] && str[i] == c)
		i++;
	while (str[i] && str[i] != c)
	{
		i++;
		len++;
	}
	return (len);
}

char	**ft_terminate(char **str, size_t index)
{
	str[index] = NULL;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	**str;

	if (!s)
		return (NULL);
	str = malloc(sizeof(str) * (ft_count_words(s, c) + 1));
	if (!str)
		return (NULL);
	i = -1;
	j = 0;
	while (++i < ft_count_words(s, c))
	{
		str[i] = malloc(sizeof(char) * (ft_word_len(&s[j], c) + 1));
		if (!str[i])
			return (NULL);
		while (s[j] == c)
			j++;
		k = 0;
		while (s[j] && s[j] != c)
			str[i][k++] = s[j++];
		str[i][k] = '\0';
	}
	return (ft_terminate(str, i));
}
