/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 21:28:12 by svalente          #+#    #+#             */
/*   Updated: 2023/11/17 19:13:53 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	heredoc_init(t_cmd **cmds, t_cmd *tmp_cmds);

int	treat_redirections(t_cmd **cmds)
{
	if ((*cmds)->redir->redir == 4)
	{
		//redir_in(cmds);
		if (!redir_in(cmds))
			return (0);
	}
	else if ((*cmds)->redir->redir == 3)
	{
		//redir_out(cmds);
		if (!redir_out(cmds))
			return (0);
	}
	else if ((*cmds)->redir->redir == 1)
	{
		//redir_out_append(cmds);
		if (!redir_out_append(cmds))
			return (0);
	}
	return (1);
}

int	redirections(t_cmd **cmds)
{
	t_cmd	*tmp_cmds;
	t_redir	*tmp_redir;

	(void)cmds;
	tmp_cmds = data()->pointer_cmd;
	if (!tmp_cmds)
		return (-1);
	quote_checker_file(cmds);
	while (data()->pointer_cmd)
	{
		tmp_redir = data()->pointer_cmd->redir;
		while (data()->pointer_cmd->redir)
		{
			if (!treat_redirections(&data()->pointer_cmd))
				break ;
				//return (0);
			data()->pointer_cmd->redir = data()->pointer_cmd->redir->next;
		}
		data()->pointer_cmd->redir = tmp_redir;
		data()->pointer_cmd = data()->pointer_cmd->next;
	}
	data()->pointer_cmd = tmp_cmds;
	if (!heredoc_init(&data()->pointer_cmd, data()->pointer_cmd))
		return (0);
	return (1);
}

int	heredoc_init(t_cmd **cmds, t_cmd *tmp_cmds)
{
	t_redir	*tmp_redir;

	if (!tmp_cmds)
		return (0);
	while (*cmds)
	{
		tmp_redir = (*cmds)->redir;
		while ((*cmds)->redir)
		{
			if ((*cmds)->redir->redir == 2)
			{
				if ((*cmds)->fd_in != -1)
					close((*cmds)->fd_in);
				(*cmds)->fd_in = heredoc((*cmds));
				if ((*cmds)->fd_in == -1)
					return (0);
			}
			(*cmds)->redir = (*cmds)->redir->next;
		}
		(*cmds)->redir = tmp_redir;
		(*cmds) = (*cmds)->next;
	}
	(*cmds) = tmp_cmds;
	return (1);
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
