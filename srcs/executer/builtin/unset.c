#include <minishell.h>

void    unset(char *cmd)
{
    t_env *node;

    node = search_env(cmd);
    if (!node)
        printf("NO NODE\n");
}