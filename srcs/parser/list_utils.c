/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 10:46:46 by svalente          #+#    #+#             */
/*   Updated: 2023/11/13 11:16:19 by svalente         ###   ########.fr       */
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

int	create_list(t_cmd **lst, char **args)
{
	int	i;

	i = -1;
	while (args[++i])
	{
		if (args[i][0] != '|')
			cmd_add_back(lst, cmd_new_node(args + i++));
		while (args[i] && args[i][0] != '|')
			i++;
		if (!args[i])
			break ;
	}
	expander(lst);
	if (!remove_empty_strs(lst))
	{
		ft_putstr_fd("ambiguous redirect\n", 2);
		free_matrix(args);
		data()->exit = 1;
		return (0);
	}
	quote_checker(lst);
	//print_list(*lst);
	free_matrix(args);
	check_redirections(lst);
	if (!redirections(lst))
		return (0);
	return (1);
}

void	print_list(t_cmd *lst)
{
	t_cmd	*tmp = lst;
	int i = 0;
	int j = 1;
	if(!lst)
	{
		printf("Empty list\n");	
		return ;
	}
	while (tmp)
	{
		printf("--------------[NODE %d]\n", j);
		i = 0;
		if (!tmp->args || !tmp->args[0])
			printf("No arguments\n");
		while (tmp->args[i])
		{
			printf("arg[%d] [%s]\n", i, tmp->args[i]);
			i++;
		}
		printf("==============\n");
		print_redir(tmp->redir);
		printf("==============\n");
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
