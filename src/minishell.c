#include "../include/minishell.h"

void free_token(t_token *token)
{
    if(token->value)
    {
        free(token->value);
        token->value = NULL;
    }
    free(token);
    token = NULL;
}

void	minishell_exit(t_minishell *minishell)
{
    if(minishell->cmd)
    {
        free_cmd_list(minishell->cmd);
        minishell->cmd = NULL;
    }
    if(minishell->line)
    {
	    free(minishell->line);
        minishell->line = NULL;
    }
    if(minishell->lexer)
    {
	    free(minishell->lexer);
        minishell->lexer = NULL;
    }
}

t_cmd *parse_input(t_lexer *lexer, char **env)
{
    t_cmd *cmd_list = NULL;  // Initialize command list
    t_cmd *curr_cmd = NULL;  // Pointer to current command node
    t_token *token;  // Token for each lexeme parsed

    token = lexer_get_next_token(lexer, env);
    while (token->type != END)
    {
        if (!cmd_list)
        {
            cmd_list = init_cmd(env);
            curr_cmd = cmd_list;
        }
        if(token->type == CMD)
        {
            store_av(curr_cmd, token->value);
            curr_cmd->ac++;
        }
        else if(token->type == PIPE)
        {
            curr_cmd = handle_pipe(curr_cmd, env);
        }
        else if (token->type == REDIR_IN || token->type == REDIR_OUT || token->type == REDIR_APPEND || token->type == HEREDOC)
        {
            t_token *tmp;

            tmp = lexer_get_next_token(lexer, env);
            add_redirection(curr_cmd, token->type, tmp->value);
            free_token(tmp);
        }
        free_token(token);
        token = lexer_get_next_token(lexer, env);
    }
    free_token(token);
    return cmd_list;
}


void print_cmd_dd(t_cmd *cmd)
{
    t_cmd *hold;

    hold = cmd;
    while(hold)
    {
        int i;
        t_redir *redirrection;

        i = 0;
        redirrection = hold->redirections;
        printf("the number of arguments is ---> %d\n", hold->ac);
        while(hold->av[i] != NULL)
            printf("the arguments is ---> %s\n", hold->av[i++]);
        while(redirrection != NULL)
        {
            printf("the file is -->%s     and    the type is --> %d --> %d\n", redirrection->file, redirrection->type,i++);
            redirrection = redirrection->next;
        }
        hold = hold->next;
    }
}

void	minishell_loop(t_minishell *minishell, char **env)
{
	minishell->env = env;
	while (1)
	{
		minishell->line = readline(LIGHT_BLUE "👾 minishell $ " RESET);
		add_history(minishell->line);
		minishell->lexer = init_lexer(minishell->line);
		if (ft_strncmp(minishell->line, "exit", 4) == 0)
			break ;
		//print_tokens(minishell->lexer, env);
        minishell->cmd = parse_input(minishell->lexer, env);
        print_cmd_dd(minishell->cmd);
        //printf("av--->%s\n", minishell->cmd->av[0]);
		//minishell->cmd = NULL;
        minishell_exit(minishell);
	}
}


int	main(int argc, char **argv, char **env)
{
	t_minishell	minishell;

	(void)argc;
	(void)argv;
	minishell_loop(&minishell, env);
	clear_history();
	minishell_exit(&minishell);
	return (0);
}
