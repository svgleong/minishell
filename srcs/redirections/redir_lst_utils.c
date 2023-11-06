/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_lst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 12:22:56 by svalente          #+#    #+#             */
/*   Updated: 2023/10/31 15:55:11 by svalente         ###   ########.fr       */
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
		// return ;
	}
	else
	{
	last = redir_last_node(*lst);
	last->next = new;
	}
	// printf("====rediraddback======\n");
	// print_redir(*lst);
	// printf("====rediraddback======\n");
}

/* void	clean_redirections(t_cmd **cmd)
{
	int		i;
	char	**clean_args;
	char	**old_args;
	char	**begin_args;
	t_cmd	*tmp;

	tmp = *cmd;
	begin_args = NULL;
	clean_args = NULL;
	while ((*cmd))
	{
		i = -1;
		if (!((*cmd)->args[0][0] == '>' || (*cmd)->args[0][0] == '<') && !begin_args)
			begin_args = copy_args_until((*cmd)->args, '<', '>');
		while ((*cmd)->args[++i])
		{
			if ((*cmd)->args[i][0] == '>' || (*cmd)->args[i][0] == '<')
			{
				clean_args = copy_args((*cmd)->args + i + 2);
				old_args = (*cmd)->args;
				(*cmd)->args = clean_args;
				free_matrix(old_args);
				i = -1;
			}
		}
		(*cmd) = (*cmd)->next;
	}
	(*cmd) = tmp;
} */

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

void	redirlstclear(t_redir **lst)
{
	t_redir	*tmp;

	//ft_putstr_fd((*lst)->file, 1);
	//write(1, "1\n", 2);
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
