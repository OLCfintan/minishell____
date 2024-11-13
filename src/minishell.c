#include "../include/minishell.h"

void free_lexer(t_lexer *lexer) {
    if (lexer != NULL) {
        // Free each dynamically allocated member within lexer, if they exist
        if (lexer->line) {
            free(lexer->line);
            lexer->line = NULL; // Nullify after freeing to avoid double-free
        }
        // Other fields in lexer, if dynamically allocated, should be freed similarly

        free(lexer);
        lexer = NULL;
    }
}


void minishell_exit(t_minishell *minishell)
{
    if (minishell->line)
    {
        free(minishell->line);
        minishell->line = NULL;
    }

}
// Function to parse input and handle pipes
t_cmd *parse_input(char *line, char **env)
{
    t_lexer *lexer = init_lexer(line);  // Initialize lexer
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
            add_redirection(curr_cmd, token->type, lexer_get_next_token(lexer, env)->value);
        }
        token = lexer_get_next_token(lexer, env);
    }
    return cmd_list;
}


void minishell_loop(t_minishell *minishell, char **env)
{
    minishell->env = env;
    t_cmd   *cmd_list;

    cmd_list = NULL;
    while(1)
    {

        minishell->line = readline(LIGHT_BLUE "👾 minishell $ " RESET);

        if(ft_strncmp(minishell->line, "exit", 4) == 0)
        {
            minishell_exit(minishell);
            break ;
        }
        add_history(minishell->line);
        cmd_list = parse_input(minishell->line, env);
        print_cmd(cmd_list);
        free_cmd_list(cmd_list);
        minishell_exit(minishell);

    }
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	minishell;

	(void)argc;
	(void)argv;
    (void)minishell;
	minishell_loop(&minishell, env);
	clear_history();
	minishell_exit(&minishell);
	return (0);
}

