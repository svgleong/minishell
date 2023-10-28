#include <minishell.h>

void	unset_node(t_env **envp, t_env *node)
{
	if (*envp == NULL || node == NULL)
		return ;
	if (*envp == node)
		*envp = node->next;
	if (node->next != NULL)
		node->next->prev = node->prev;
	if (node->prev != NULL)
		node->prev->next = node->next;
	if (node->content)
		free(node->content);
	free(node);
}

void	unset(char **cmd)
{
	int		i;
	t_env	*node;

	i = 0;
	while (cmd[i])
	{
		node = search_env(cmd[i]);
		if (node)
			unset_node(&data()->envp, node);
		i++;
	}
	data()->exit = EXIT_SUCCESS;
}
