/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_lst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 12:22:56 by svalente          #+#    #+#             */
/*   Updated: 2023/10/14 19:08:23 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_redir *redir_new_node(int redir, char *file)
{
	t_redir *new;

	new = ft_calloc(1, sizeof(t_redir));
	if (!new)
		return (NULL);
	new->fd = -1;
	new->redir = redir;
	new->file = ft_strdup(file);
	new->next = NULL;
	return (new);
}

t_redir *redir_last_node(t_redir *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void    redir_add_back(t_redir **lst, t_redir *new)
{
	t_redir	*last;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = redir_last_node(*lst);
	last->next = new;
}

void	clean_redirections(t_cmd **cmd)
{
	int		i;
	char	**clean_args;
	char	**old_args;
	t_cmd	*tmp;

	tmp = *cmd;
	while ((*cmd))
	{
		i = -1;
		while ((*cmd)->args[++i])
		{
			if (!((*cmd)->args[i][0] == '>' || (*cmd)->args[i][0] == '<'))
			{
				clean_args = copy_args_until((*cmd)->args, '<', '>');
				old_args = (*cmd)->args;
				(*cmd)->args = clean_args;
				free_matrix(old_args);
				continue ;
			}
			if ((*cmd)->args[i][0] == '>' || (*cmd)->args[i][0] == '<')
			{
				clean_args = copy_args((*cmd)->args + i + 2);
				old_args = (*cmd)->args;
				(*cmd)->args = clean_args;
				free_matrix(old_args);
				i = -1;
				continue ;
			}
		}
		(*cmd) = (*cmd)->next;
	}
	(*cmd) = tmp;
}

void	create_redir_lst(t_cmd **cmd, int redir, char *file)
{
	redir_add_back(&(*cmd)->redir, redir_new_node(redir, file));
	//printf("redir: %d file: \n", redir);
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
		(*cmds) = (*cmds)->next;
	}
	(*cmds) = head;
	while ((*cmds))
	{
		clean_redirections(cmds);
		(*cmds) = (*cmds)->next;
	}
	(*cmds) = head;
	//print_list(*cmds);
}

void	redirlstclear(t_redir **lst)
{
	t_redir	*tmp;

	while (*lst)
	{
		tmp = *lst;
		(*lst) = (*lst)->next;
		free(tmp->file);
		if (tmp->fd != -1)
			close(tmp->fd);
		free(tmp);
	}
	*lst = NULL;
}
