#include "store.h"
// Function to initialize a redirection node
t_redir *init_redirection(t_types type, char *file)
{
    t_redir *redir = malloc(sizeof(t_redir));
    if (!redir)
        return NULL;
    redir->type = type;
    redir->file = ft_strdup(file);  // Assuming you have a `ft_strdup` function
    redir->next = NULL;
    return redir;
}


void add_redirection(t_cmd *cmd, t_types type, char *file)
{
    t_redir *redir = init_redirection(type, file);

    // Add the redirection to the linked list of redirections for this command
    if (!cmd->redirections)
    {
        cmd->redirections = redir;
    }
    else
    {
        t_redir *last = cmd->redirections;
        while (last->next)
        {
            last = last->next;
        }
        last->next = redir;
    }
}

