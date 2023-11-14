/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:15:09 by svalente          #+#    #+#             */
/*   Updated: 2023/11/14 15:15:55 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exec_error(char *s, int exit_code)
{
	ft_putstr_fd(s, STDERR_FILENO);
	data()->exit = exit_code;
}

void	heredoc_exception(t_cmd *cmd)
{
	if (pipe(cmd->pipe) == -1)
		printf("pipe error\n");
	if (cmd->next->fd_in == -1)
		cmd->next->fd_in = dup(cmd->pipe[0]);
	close(cmd->pipe[0]);
	close(cmd->pipe[1]);
}
