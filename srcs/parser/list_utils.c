/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parallels <parallels@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 10:46:46 by svalente          #+#    #+#             */
/*   Updated: 2023/10/13 15:24:38 by parallels        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmd.h>
#include <alloc.h>
#include "../../includes/alloc.h"
#include <minishell.h>

t_cmd *new_node(char **args)
{
	t_cmd *new;

	new = ft_calloc(1, sizeof(t_cmd));
	if (!new)
		return (NULL);
	if (args)
		new->args = copy_matrix(args);
	new->prev = NULL;
	new->next = NULL;
	new->fd_in = 0;
	new->fd_out = 1;
	new-> redir = -1;
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

/* void	create_list(char *rl, t_cmd **lst)
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
} */

void	create_list(t_cmd **lst, char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (args[i][0] != '|')
		{
			//printf("ARGS[%d] %s\n",i, args[i]);
			add_back(lst, new_node(args + i));
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
	print_list(*lst);
	remove_quotes(lst);
	free_matrix(args);
}

//fsafafs | fasfaf |F asfasfasf

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
		//printf("[Node %d]\n", j);
		i = 0;
		while (tmp->args[i])
		{
			//printf("arg[%d] %s\n", i, tmp->args[i]);
			i++;
		}
		//printf("redir %d fd_in %d fd_out %d\n", tmp->redir, tmp->fd_in, tmp->fd_out);
		tmp = tmp->next;
		j++;
	}
	printf("---------------------\n");
}

void	cmdlstclear(t_cmd **lst)
{
	t_cmd *tmp;

	//printf("Clearing list\n");
	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free_matrix(tmp->args);
		free(tmp);
	}
	*lst = NULL;
}

/* void	envlstclear()
{
	t_env *tmp;

	while (*lst)
	{
		
	}
	*lst = NULL;
} */