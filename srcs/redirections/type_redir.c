/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 20:49:02 by svalente          #+#    #+#             */
/*   Updated: 2023/11/17 11:21:29 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	redir_in(t_cmd **cmds)
{
	data()->redir = 1;
	if ((*cmds)->fd_in != -1)
		close((*cmds)->fd_in);
	if (access((*cmds)->redir->file, F_OK) == -1)
	{
		perror("Error");
		data()->exit = 1;
		(*cmds)->error = true;
		return (0);
	}
	(*cmds)->fd_in = open((*cmds)->redir->file, O_RDONLY);
	if ((*cmds)->fd_in == -1)
	{
		perror("Error");
		data()->exit = 1;
		(*cmds)->error = true;
		return (0);
	}
	return (1);
}

int	redir_out(t_cmd **cmds)
{
	data()->redir = 1;
	if ((*cmds)->fd_out != -1)
		close((*cmds)->fd_out);
	(*cmds)->fd_out = open((*cmds)->redir->file, O_WRONLY | O_CREAT \
		| O_TRUNC, 0644);
	if ((*cmds)->fd_out == -1)
	{
		perror("Error");
		data()->exit = 1;
		return (0);
	}
	return (1);
}

int	redir_out_append(t_cmd **cmds)
{
	data()->redir = 1;
	if ((*cmds)->fd_out != -1)
		close((*cmds)->fd_out);
	(*cmds)->fd_out = open((*cmds)->redir->file, O_WRONLY | O_CREAT \
		| O_APPEND, 0644);
	if ((*cmds)->fd_out == -1)
	{
		perror("Error");
		data()->exit = 1;
		data()->error = 1;
		return (0);
	}
	return (1);
}
