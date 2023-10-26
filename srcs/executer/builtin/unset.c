#include <minishell.h>

void unset_node(t_env **envp, t_env *node)
{
    if (*envp == NULL || node == NULL)
        return;
    if (*envp == node)
        *envp = node->next;
    if (node->next != NULL)
        node->next->prev = node->prev;
    if (node->prev != NULL)
        node->prev->next = node->next;
    free(node);
}

void    unset(char **cmd)
{
    int i = 0;
    t_env *node;
    while (cmd[i])
    {
        node = search_env(cmd[i]);
        if (node)
            unset_node(&data()->envp, node);
        i++;
    }
}