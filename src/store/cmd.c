#include "store.h"

t_cmd *init_cmd(char **env)
{
    t_cmd *cmd = malloc(sizeof(t_cmd));
    if (!cmd) return NULL;
    cmd->ac = 0;
    cmd->av = malloc(sizeof(char *));
    cmd->av[0] = NULL;
    cmd->env = env;
    cmd->redirections = NULL;
    cmd->next = NULL;
    return cmd;
}


/*void execute_single_cmd(t_cmd *cmd)
{
    int fd_in ;
    int fd_out;

    // Handle redirections
    fd_in = -1;
    fd_out = -1;
    while (cmd->redirections) {
        if (cmd->redirections->type == REDIR_IN)
            fd_in = open(cmd->redirections->file, O_RDONLY);
        else if (cmd->redirections->type == REDIR_OUT)
            fd_out = open(cmd->redirections->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        else if (cmd->redirections->type == REDIR_APPEND)
            fd_out = open(cmd->redirections->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
        // Implement heredoc redirection if needed
        cmd->redirections = cmd->redirections->next;
    }

    // Execute the command (e.g., using execvp)
    if (fd_in != -1) dup2(fd_in, STDIN_FILENO);
    if (fd_out != -1) dup2(fd_out, STDOUT_FILENO);
    execvp(cmd->av[0], cmd->av);
    perror("Execution failed");
}
*/
/*void free_cmd_list(t_cmd *cmd_list)
{
    t_cmd *current;

    current = cmd_list;

    while (current) {
        t_cmd *tmp;

        tmp = current;
        if (current->av)
        {
            for (int i = 0; current->av[i]; i++)
            {
                free(current->av[i]);
            }
            free(current->av);
        }
        if (current->redirections)
        {
            t_redir *redir_tmp;

            redir_tmp = NULL;
            while (current->redirections) {
                redir_tmp = current->redirections;
                free(redir_tmp->file);
                current->redirections = redir_tmp->next;
                free(redir_tmp);
            }
        }
        current = current->next;
        free(tmp);
    }
}*/

/*
void execute_cmds(t_cmd *cmd_list, char **env)
{
    (void)env;
    t_cmd *current = cmd_list;

    while (current) {
        // Execute command, handle redirections
        execute_single_cmd(current);
        current = current->next;
    }
}*/

#include "../../include/minishell.h"

void free_cmd_list(t_cmd *cmd_list) {
    t_cmd *current;

    while (cmd_list) {
        current = cmd_list;
        
        // Free each argument in av
        if (cmd_list->av) {
            for (int i = 0; cmd_list->av[i]; i++) {
                free(cmd_list->av[i]);
            }
            free(cmd_list->av); // Free the array itself
        }
        
        // Free redirection list
        t_redir *redir = cmd_list->redirections;
        while (redir) {
            t_redir *tmp_redir = redir;
            free(redir->file); // Free file path
            redir = redir->next;
            free(tmp_redir); // Free redirection structure
        }
        
        // Move to the next command in the pipeline
        cmd_list = cmd_list->next;
        free(current); // Free the command structure
    }
}


void store_av(t_cmd *cmd, char *av)
{
    if(!av)
        return ;
    int i = 0;
    while (cmd->av[i])
        i++;
    cmd->av = realloc(cmd->av, (i + 2) * sizeof(char *));
    cmd->av[i] = ft_strdup(av);
    cmd->av[i + 1] = NULL;
}

