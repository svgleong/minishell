/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 10:46:46 by svalente          #+#    #+#             */
/*   Updated: 2023/09/20 13:57:17 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

t_cmd *new_node(char *cmd)
{
	t_cmd *new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->prev = NULL;
	new->next = NULL;
	new->cmd = cmd;
	new->args = NULL;
	return (new);
}

t_cmd	*last_node(t_cmd *lst)
{
	if (!lst)
		return (NULL);
	
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	add_back(t_cmd **lst, t_cmd *new)
{
	t_cmd *last;
	
	if (!*lst)
	{
		*lst = new;
		new->prev = NULL;
		printf("debug\n");
		return ;
	}
	last = last_node(*lst);
	last->next = new;
	last->next->prev = last;
}

void	create_list(char *rl, t_cmd **lst)
{
	char 	**cmds;
	int		i = 0;

	cmds = ft_split(rl, '|');
	while (cmds[i])
	{
		add_back(lst, new_node(cmds[i]));
		i++;
	}
}

void	print_list(t_cmd *lst)
{
	t_cmd *tmp = lst;

	if(!lst)
	{
		printf("Empty list\n");	
		return ;
	}
	while (tmp)
	{
		printf("%s\n", tmp->cmd);
		tmp = tmp->next;
	}
	printf("\n");
}

void	cmdlstclear(t_cmd **lst)
{
	t_cmd *tmp;

	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp->cmd);
		free(tmp);
	}
	*lst = NULL;
}