/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:42:07 by svalente          #+#    #+#             */
/*   Updated: 2023/11/13 20:45:18 by svalente         ###   ########.fr       */
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

	head = (*cmds);
	while (*cmds)
	{
		i = -1;
		j = 0;
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

int	count_redir(char **args)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (args[++i])
	{
		if (args[i][0] == '>' || args[i][0] == '<')
			count += 2;
	}
	return (count);
}

int	matrix_size(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	i += count_redir(args);
	return (i);
}

t_redir	*get_head_redir(t_redir *lst)
{
	while (lst && lst->prev)
		lst = lst->prev;
	return (lst);
}

void	redirlstclear(t_redir **lst)
{
	t_redir	*head;
	t_redir	*tmp;

	head = get_head_redir(*lst);
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->file);
		if (tmp->fd != -1)
			close(tmp->fd);
		free(tmp);
	}
	head = NULL;
}
