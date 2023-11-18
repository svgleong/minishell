/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:41:17 by svalente          #+#    #+#             */
/*   Updated: 2023/11/13 21:06:42 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	unset(char **cmd)
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
	return (EXIT_SUCCESS);
}
