/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 10:46:46 by svalente          #+#    #+#             */
/*   Updated: 2023/09/25 14:38:38 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmd.h>
#include <alloc.h>
#include "../../includes/alloc.h"

t_cmd *new_node( char **args)
{
	t_cmd *new;

	new = ft_calloc(1, sizeof(t_cmd));//malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	if (args)
		new->args = copy_matrix(args);
	/* for (int i = 0; args[i] != NULL; i++)
		printf("Args[%d] %s\n", i, args[i]);   */
	new->prev = NULL;
	new->next = NULL;
	//printf("args[0]: %s\n", new->args[0]);
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
	char 	**args;
	// Funcao que vai verificar as quotes e pipes, ter em atencao se tiver dentro de quotes 
	// "|" "  |  "
	cmds = ft_split(rl, '|');
	while (cmds[i])
	{
		//printf("cmds[%d]: %s\n", i, cmds[i]);
		// Funcao que verifica se as quotes sao validas
		// Transformar o split para ter em conta as quotes e depois sim podes fazer split (se achares que es capaz tens incluir a divisao das redirections) 
		args = ft_split(cmds[i], ' ');
		add_back(lst, new_node(args));
		i++;
	}
	i = -1;
	while (cmds[++i])
		free(cmds[i]);
}

void	print_list(t_cmd *lst)
{
	t_cmd *tmp = lst;
	int i = 0;

	if(!lst)
	{
		printf("Empty list\n");	
		return ;
	}
	while (tmp)
	{
		i = 0;
		while (tmp->args[i])
		{
			printf("arg[%d] %s\n", i, tmp->args[i]);
			i++;
		}
		tmp = tmp->next;
	}
}

void	cmdlstclear(t_cmd **lst)
{
	t_cmd *tmp;

	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free_matrix(tmp->args);
		free(tmp);
	}
	*lst = NULL;
}