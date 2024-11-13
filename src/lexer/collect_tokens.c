
#include "../../include/minishell.h"

t_token	*lexer_collect_larrow(t_lexer *lexer)
{
	char	*value;

	lexer_advance(lexer);
	if (lexer->c == '<')
	{
		lexer_advance(lexer);
		value = ft_strdup("<<");
		return (init_token(value, HEREDOC));
	}
	value = ft_strdup("<");
	return (init_token(value, REDIR_IN));
}

t_token	*lexer_collect_rarrow(t_lexer *lexer)
{
	char	*value;

	lexer_advance(lexer);
	if (lexer->c == '>')
	{
		lexer_advance(lexer);
		value = ft_strdup(">>");
		return (init_token(value, REDIR_APPEND));
	}
	value = ft_strdup(">");
	return (init_token(value, REDIR_OUT));
}

t_token	*lexer_collect_cmd(t_lexer *lexer, char **env)
{
	char	*value;

	value = ft_strdup("");
	while (lexer->c != '\0' && ft_isprint(lexer->c))
	{
		if (lexer->c == '$')
		{
			lexer_advance(lexer);
			value = ft_strjoin(value, lexer_get_env_value(lexer, env));
			continue ;
		}
		value = ft_strjoin_char(value, lexer->c);
		lexer_advance(lexer);
	}
	return (init_token(value, CMD));
}

t_token	*lexer_collect_squote(t_lexer *lexer)
{
	char	*value;

	lexer_advance(lexer);
	value = ft_strdup("");
	while (lexer->c != '\'' && lexer->c != '\0')
	{
		value = ft_strjoin_char(value, lexer->c);
		lexer_advance(lexer);
	}
	lexer_advance(lexer);
	return (init_token(value, CMD));
}

t_token	*lexer_collect_dquote(t_lexer *lexer, char **env)
{
	char	*value;

	lexer_advance(lexer);
	value = ft_strdup("");
	while (lexer->c != '\"' && lexer->c != '\0')
	{
		if (lexer->c == '$')
		{
			lexer_advance(lexer);
			value = ft_strjoin(value, lexer_get_env_value(lexer, env));
			continue ;
		}
		else
			value = ft_strjoin_char(value, lexer->c);
		lexer_advance(lexer);
	}
	lexer_advance(lexer);
	return (init_token(value, CMD));
}
