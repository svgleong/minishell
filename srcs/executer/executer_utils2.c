/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:15:09 by svalente          #+#    #+#             */
/*   Updated: 2023/11/14 22:02:07 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exec_error(char *cmd, char *s, int exit_code)
{
	data()->exit = exit_code;
	if (cmd)
		ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(s, STDERR_FILENO);
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
