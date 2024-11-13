
#include "../../include/minishell.h"

void	print_tokens(t_lexer *lexer, char **env)
{
	t_token	*token;

	printf("|-----------------|-----------------|\n");
	printf("|      value      |       type      |\n");
	printf("|-----------------|-----------------|\n");
	token = lexer_get_next_token(lexer, env);
	while (token->type != END)
	{
		printf("|%17s|%17d|\n", token->value, token->type);
		free(token->value);
		free(token);
		token = lexer_get_next_token(lexer, env);
	}
	printf("|-----------------|-----------------|\n");
	free(token->value);
	free(token);
	token = NULL;
}
