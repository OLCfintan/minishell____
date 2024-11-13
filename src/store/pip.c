#include "store.h"
// Function to handle pipe and create a new command node
t_cmd *handle_pipe(t_cmd *curr_cmd, char **env)
{
    // Create a new command node
    curr_cmd->next = init_cmd(env);
    // Move to the newly created node
    return curr_cmd->next;
}

