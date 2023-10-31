/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 10:46:46 by svalente          #+#    #+#             */
/*   Updated: 2023/10/19 08:56:16 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include <cmd.h>
#include <alloc.h>
#include "../../includes/alloc.h" */
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

void	create_list(t_cmd **lst, char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (args[i][0] != '|')
		{
			cmd_add_back(lst, cmd_new_node(args + i));
			i++;
		}
		while (args[i] && args[i][0] != '|')
			i++;
		if (!args[i])
			break ;
		i++;
	}
	//print_list(*lst);
	expander(lst);
	remove_empty_strs(lst);
	remove_quotes(lst);
	free_matrix(args);
	check_redirections(lst);
	redirections(lst);
	print_list(*lst);
}

void	print_list(t_cmd *lst)
{
	t_cmd *tmp = lst;
	int i = 0;
	int j = 1;
	if(!lst)
	{
		printf("Empty list\n");	
		return ;
	}
	while (tmp)
	{
		printf("[Node %d]\n", j);
		i = 0;
		if (!tmp->args)
			printf("No arguments\n");
		while (tmp->args[i])
		{
			printf("arg[%d] [%s]\n", i, tmp->args[i]);
			i++;
		}
		print_redir(lst->redir);
		printf("fd_in: %d\n", tmp->fd_in);
		printf("fd_out: %d\n", tmp->fd_out);
		tmp = tmp->next;
		j++;
	}
	printf("---------------------\n");
}

void	cmdlstclear(t_cmd **lst)
{
	t_cmd	*tmp;

	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free_matrix(tmp->args);
		if (tmp->redir)
			redirlstclear(&tmp->redir);
		free(tmp);
	}
	*lst = NULL;
}
