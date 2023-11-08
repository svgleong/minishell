/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_lst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 12:22:56 by svalente          #+#    #+#             */
/*   Updated: 2023/11/07 09:31:27 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_redir	*redir_new_node(int redir, char *file)
{
	t_redir	*new;

	new = ft_calloc(1, sizeof(t_redir));
	if (!new)
		return (NULL);
	new->fd = -1;
	new->redir = redir;
	new->file = ft_strdup(file);
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

t_redir	*redir_last_node(t_redir *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	redir_add_back(t_redir **lst, t_redir *new)
{
	t_redir	*last;

	if (!*lst)
	{
		*lst = new;
		new->prev = NULL;
		// return ;
	}
	else
	{
	last = redir_last_node(*lst);
	last->next = new;
	last->next->prev = last;
	}
	// printf("====rediraddback======\n");
	// print_redir(*lst);
	// printf("====rediraddback======\n");
}

void	create_redir_lst(t_cmd **cmd, int redir, char *file)
{
	// printf("redir: file %p")
	redir_add_back(&(*cmd)->redir, redir_new_node(redir, file));
}

void	print_redir(t_redir *lst)
{
	t_redir *tmp = lst;

	if (!lst)
	{
		printf("Empty list for redirections\n");	
		return ;
	}
	while (tmp)
	{
		// printf("Address of red: %p\n", tmp);
		// printf("Address of file: %p\n", tmp->file);
		printf("redir: %d\n", tmp->redir);
		printf("file: %s\n", tmp->file);
		tmp = tmp->next;
	}
}

void	check_redirections(t_cmd **cmds)
{
	t_cmd	*head;
	int		i;

	head = (*cmds);
	while ((*cmds))
	{
		i = -1;
		while ((*cmds)->args[++i])
		{
			if (!ft_strncmp((*cmds)->args[i], ">>", 2))
				create_redir_lst(cmds, 1, (*cmds)->args[i + 1]);
			else if (!ft_strncmp((*cmds)->args[i], "<<", 2))
				create_redir_lst(cmds, 2, (*cmds)->args[i + 1]);
			else if (!ft_strncmp((*cmds)->args[i], ">", 2))
				create_redir_lst(cmds, 3, (*cmds)->args[i + 1]);
			else if (!ft_strncmp((*cmds)->args[i], "<", 2))
				create_redir_lst(cmds, 4, (*cmds)->args[i + 1]);
		}
		/* print_redir((*cmds)->redir);
		printf("==============\n"); */
		(*cmds) = (*cmds)->next;
	}
	(*cmds) = head;
	clean_redirections(cmds);
	// print_list(*cmds);
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
