/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 10:46:46 by svalente          #+#    #+#             */
/*   Updated: 2023/11/13 19:53:18 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_cmd	*cmd_new_node(char **args)
{
	t_cmd	*new;

	new = ft_calloc(1, sizeof(t_cmd));
	if (!new)
		return (NULL);
	if (args)
		new->args = copy_matrix(args);
	new->prev = NULL;
	new->next = NULL;
	new->redir = NULL;
	new->fd_in = -1;
	new->fd_out = -1;
	return (new);
}

t_cmd	*cmd_last_node(t_cmd *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	cmd_add_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*last;

	if (!*lst)
	{
		*lst = new;
		new->prev = NULL;
		return ;
	}
	last = cmd_last_node(*lst);
	last->next = new;
	last->next->prev = last;
}

void	cmdlstclear(t_cmd **lst)
{
	t_cmd	*tmp;

	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free_matrix(tmp->args);
		if (tmp->fd_in != -1)
			close(tmp->fd_in);
		if (tmp->fd_out != -1)
			close(tmp->fd_out);
		if (tmp->redir)
			redirlstclear(&tmp->redir);
		free(tmp);
	}
	*lst = NULL;
}
