
#ifndef MINISHELL_H
# define MINISHELL_H

// Includes
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdint.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../src/utils/utils.h"
/* ===== Color ===== */
# define LIGHT_BLUE "\x1B[1;34m"
# define RESET "\x1B[0m"





/////
typedef enum s_types
{
	CMD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC,
	END,
}	t_types;

typedef struct s_lexer
{
	char	*line;
	size_t	line_len;
	char	c;
	size_t	i;
}	t_lexer;

typedef struct s_token
{
	char			*value;
	t_types			type;
	struct s_token	*next;
}	t_token;

typedef struct s_parser
{
	t_token			*token;
	struct s_parser	*curr;
	struct s_parser	*next;
}	t_parser;

typedef struct s_minishell
{
	char	*line;
	t_lexer	*lexer;
	char	**env;
}	t_minishell;
//

typedef struct s_redir//for reddirections
{
    char *file;
    t_types type;
    struct s_redir *next;
}  t_redir;

typedef struct s_cmd // each node is a command without pip so if moving to next node means to next pip
{
    int ac;
    int exit;
    char **av;// store line without reddirection
    char **env;//store envirment
    t_redir *redirections;//store name of files for in and out and the type of reddirections
    struct s_cmd *next;//means next pip
}  t_cmd;
/* ===== Prototypes ===== */

// Minishell
void	minishell_loop(t_minishell *minishell, char **env);
void	minishell_exit(t_minishell *minishell);
// Tokens
t_token	*init_token(char *value, t_types type);
void	print_tokens(t_lexer *lexer, char **env);
// Lexer
t_lexer	*init_lexer(char *line);
void	lexer_advance(t_lexer *lexer);
t_token	*lexer_advance_with(t_token *token, t_lexer *lexer);
char	*lexer_get_env_value(t_lexer *lexer, char **env);
t_token	*lexer_collect_cmd(t_lexer *lexer, char **env);
t_token	*lexer_collect_squote(t_lexer *lexer);
t_token	*lexer_collect_dquote(t_lexer *lexer, char **env);
t_token	*lexer_collect_rarrow(t_lexer *lexer);
t_token	*lexer_collect_larrow(t_lexer *lexer);
// Tokenizer
t_token	*lexer_get_next_token(t_lexer *lexer, char **env);
// Utils
char	*ft_strjoin_char(char *s1, char c);



//store
void add_redirection(t_cmd *cmd, t_types type, char *file);
void store_av(t_cmd *cmd, char *av);
void execute_cmds(t_cmd *cmd_list, char **env);
void free_cmd_list(t_cmd *cmd_list);
void execute_single_cmd(t_cmd *cmd);
void    print_cmd(t_cmd *cmd_list);


t_redir *init_redirection(t_types type, char *file);

t_cmd *handle_pipe(t_cmd *curr_cmd, char **env);
t_cmd *init_cmd(char **env);

#endif
