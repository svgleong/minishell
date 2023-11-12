/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 21:28:12 by svalente          #+#    #+#             */
/*   Updated: 2023/11/12 14:39:51 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	redir_in(t_cmd **cmds);
static int	redir_out(t_cmd **cmds);
static int	redir_out_append(t_cmd **cmds);
void		heredoc_init(t_cmd **cmds);

int	treat_redirections (t_cmd **cmds)
{
	if ((*cmds)->redir->redir == 4)
	{
		if (!redir_in(cmds))
			return (0);
	}
	else if ((*cmds)->redir->redir == 3)
	{
		if(!redir_out(cmds))
			return (0);
	}
	else if ((*cmds)->redir->redir == 1)
	{
		if (redir_out_append(cmds))
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
	while (data()->pointer_cmd)
	{
		tmp_redir = data()->pointer_cmd->redir;
		while (data()->pointer_cmd->redir)
		{
			if (!treat_redirections(&data()->pointer_cmd))
				return (0);
			data()->pointer_cmd->redir = data()->pointer_cmd->redir->next;
		}
		data()->pointer_cmd->redir = tmp_redir;
		data()->pointer_cmd = data()->pointer_cmd->next;
	}
	data()->pointer_cmd = tmp_cmds;
	heredoc_init(&data()->pointer_cmd);
	return (1);
}

void	heredoc_init(t_cmd **cmds)
{
	t_cmd	*tmp_cmds;
	t_redir	*tmp_redir;

	tmp_cmds = *cmds;
	if (!tmp_cmds)
		return ;
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
      }
			(*cmds)->redir = (*cmds)->redir->next;
		}
		(*cmds)->redir = tmp_redir;
		(*cmds) = (*cmds)->next;
	}
	(*cmds) = tmp_cmds;
}

static int	redir_in(t_cmd **cmds)
{
	data()->redir = 1;
	if ((*cmds)->fd_in != -1)
		close((*cmds)->fd_in);
	if (access((*cmds)->redir->file, F_OK) == -1)
	{
		perror("Error");
		data()->exit = 1;
		return (0);
	}
	(*cmds)->fd_in = open((*cmds)->redir->file, O_RDONLY);
	if ((*cmds)->fd_in == -1)
	{
		ft_putstr_fd("Error opening file\n", 2);
		data()->exit = 1;
		return (0);
	}
	return (1);
}

static int	redir_out(t_cmd **cmds)
{
	data()->redir = 1;
	if ((*cmds)->fd_out != -1)
		close((*cmds)->fd_out);
	(*cmds)->fd_out = open((*cmds)->redir->file, O_WRONLY | O_CREAT \
		| O_TRUNC, 0644);
	if ((*cmds)->fd_out == -1)
	{
		ft_putstr_fd("Error opening file\n", 2);
		data()->exit = 1;
		return (0);
	}
	return (1);
}

static int	redir_out_append(t_cmd **cmds)
{
	data()->redir = 1;
	if ((*cmds)->fd_out != -1)
		close((*cmds)->fd_out);
	(*cmds)->fd_out = open((*cmds)->redir->file, O_WRONLY | O_CREAT \
		| O_APPEND, 0644);
	if ((*cmds)->fd_out == -1)
	{
		ft_putstr_fd("Error opening file\n", 2);
		data()->exit = 1;
		data()->error = 1;
		return (0);
	}
	return (1);
}
