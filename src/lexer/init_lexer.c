
#include "../../include/minishell.h"

t_lexer	*init_lexer(char *line)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->line = line;
	lexer->line_len = ft_strlen(line);
	lexer->i = 0;
	lexer->c = line[lexer->i];
	return (lexer);
}

void	lexer_advance(t_lexer *lexer)
{
	if (lexer->c != '\0' && lexer->i < ft_strlen(lexer->line))
	{
		lexer->i++;
		lexer->c = lexer->line[lexer->i];
	}
}

t_token	*lexer_advance_with(t_token *token, t_lexer *lexer)
{
	lexer_advance(lexer);
	return (token);
}

t_token	*lexer_get_next_token(t_lexer *lexer, char **env)
{
	while (lexer->c != '\0')
	{
		if (ft_iswp(lexer->c))
			lexer_advance(lexer);
		if (ft_isprint(lexer->c))
			return (lexer_collect_cmd(lexer, env));
		if (lexer->c == '|')
			return (lexer_advance_with(
					init_token(ft_strdup("|"), PIPE), lexer));
		if (lexer->c == '\'')
			return (lexer_collect_squote(lexer));
		if (lexer->c == '\"')
			return (lexer_collect_dquote(lexer, env));
		if (lexer->c == '<')
			return (lexer_collect_larrow(lexer));
		if (lexer->c == '>')
			return (lexer_collect_rarrow(lexer));
	}
	return (init_token(ft_strdup("EOF"), END));
}
