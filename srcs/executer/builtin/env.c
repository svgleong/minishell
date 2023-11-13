/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:41:17 by svalente          #+#    #+#             */
/*   Updated: 2023/11/13 19:42:57 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// find last node in list
t_env	*env_last_node(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

// adds the created node in the last position
void	env_add_node_end(t_env *lst, t_env *new)
{
	if (lst)
	{
		new->prev = env_last_node(lst);
		env_last_node(lst)->next = new;
	}
	else
		lst = new;
}

// creates and allocs new node putting env str in content
t_env	*env_new_node(char *str)
{
	t_env	*new;

	new = ft_calloc(sizeof(t_env), 1);
	if (!new)
		return (NULL);
	new->content = ft_strdup(str);
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void	update_shell_lvl(void)
{
	t_env	*node;
	char	**var_value;
	int		lvl;

	var_value = NULL;
	node = search_env("SHLVL");
	if (node == NULL)
		env_add_node_end(data()->envp, env_new_node("SHLVL=1"));
	else
	{
		var_value = ft_split(node->content, '=');
		lvl = ft_atoi(var_value[1]);
		free(node->content);
		node->content = ft_strjoin_free("SHLVL=", ft_itoa(++lvl), 2);
	}
	free_matrix(var_value);
}

void	envp(void)
{
	t_env	*env;

	env = data()->envp;
	while (env && env->content)
	{
		if (ft_strchr(env->content, '=') && ft_strncmp(env->content, "_", 1))
			printf("%s\n", env->content);
		env = env->next;
	}
	exitbuiltin(EXIT_SUCCESS);
}
