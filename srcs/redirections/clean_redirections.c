/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:42:07 by svalente          #+#    #+#             */
/*   Updated: 2023/10/17 12:31:19 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	matrix_size(char **args);

void	clean_redirections(t_cmd **cmds)
{
	int		i;
	int		j;
	t_cmd	*head;
	char	**new_matrix;

	j = 0;
	head = (*cmds);
	while (*cmds)
	{
		i = -1;
		new_matrix = ft_calloc(matrix_size((*cmds)->args) + 1, sizeof(char *));
		while ((*cmds)->args[++i])
		{
			if ((*cmds)->args[i][0] == '>' || (*cmds)->args[i][0] == '<')
			{
				i++;
				continue ;
			}
			new_matrix[j++] = ft_strdup((*cmds)->args[i]);
		}
		free_matrix((*cmds)->args);
		(*cmds)->args = new_matrix;
		(*cmds) = (*cmds)->next;
	}
	(*cmds) = head;
}

int	matrix_size(char **args)
{
	int	i;
	
	i = 0;
	while (args[i])
		i++;
	return (i);
}
