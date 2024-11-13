#include "../../include/minishell.h"


void execute_single_cmd(t_cmd *cmd)
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
    if (fd_in != -1) 
        dup2(fd_in, STDIN_FILENO);
    if (fd_out != -1) 
        dup2(fd_out, STDOUT_FILENO);
    execvp(cmd->av[0], cmd->av);
    perror("Execution failed");
}



void execute_cmds(t_cmd *cmd_list, char **env)
{
    (void)env;
    t_cmd *current = cmd_list;

    while (current) {
        // Execute command, handle redirections
        execute_single_cmd(current);
        current = current->next;
    }
}


