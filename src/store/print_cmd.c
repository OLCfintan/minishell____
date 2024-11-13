#include "store.h"

void    print_cmd(t_cmd *cmd_list)
{
    if(!cmd_list)
        return ;
    t_redir *tmp;
    t_cmd *temp;

    temp = cmd_list;
    tmp = temp->redirections;
    while(temp)
    {
        int i;

        i = 0;
        while(temp->av[i] != NULL)
        {
            printf("the number of arguments is ---->%d\n", temp->ac);
            printf("argumnet is -->%s\n", temp->av[i++]);
        }
        if(tmp != NULL)
        {
            while(tmp)
            {
                printf("file is ---> %s  and type is %d\n", tmp->file, (int)tmp->type);
                tmp = tmp->next;
            }
        }
        temp = temp->next;
    }
}
