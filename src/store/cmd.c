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


void free_cmd_list(t_cmd *cmd_list) 
{
    t_cmd *current;

    current = NULL;
    while (cmd_list)
    {
        current = cmd_list;

        // Free each argument in av
        if (cmd_list->av) {
            for (int i = 0; cmd_list->av[i]; i++) {
                free(cmd_list->av[i]);
            }
            free(cmd_list->av);
            cmd_list->av = NULL; // Free the array itself
        }

        // Free redirection list
        t_redir *redir = cmd_list->redirections;
        while (redir) {
            t_redir *tmp_redir = redir;
            free(redir->file); // Free file path
            redir = redir->next;
            free(tmp_redir); 
            tmp_redir = NULL;// Free redirection structure
        }

        // Move to the next command in the pipeline
        cmd_list = cmd_list->next;
        free(current);
        current = NULL; // Free the command structure
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

