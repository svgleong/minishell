#include <minishell.h>

char	*node_value(t_env *node)
{
	char	**key_value;
	char	*value;

	if (!node)
		return (NULL);
	key_value = ft_split(node->content, '=');
	value = ft_strdup(key_value[1]);
	free_matrix(key_value);
	return (value);
}

void    free_env_list(t_env **lst)
{
    t_env	*temp;
	
	while (*lst)
	{
		temp = (*lst)->next;
		free((*lst)->content);
		free((*lst));
		*lst = temp;
	}
	//*lst = NULL;
}

t_cmd	*get_head(t_cmd *lst)
{
	while (lst && lst->prev)
		lst = lst->prev;
	return (lst);
}

void	general_free(t_cmd *cmd, bool env, bool close_fds, bool to_exit)
{
	cmd = get_head(cmd);
	//print_list(cmd);
	if (cmd)
		cmdlstclear(&cmd);
	if (env)
		if (data()->envp)
			free_env_list(&data()->envp);
	if (close_fds)
	{
		close(0);
		close(1);
		close(2);
	}
	if (to_exit)
		exit(data()->exit);
}
