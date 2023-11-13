/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_checker.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:12:33 by svalente          #+#    #+#             */
/*   Updated: 2023/11/08 12:28:05 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	has_file(t_cmd *cmd)
{
	t_redir	*head;

	head = cmd->redir;
	while (cmd->redir)
	{
		if (!cmd->redir->file)
			return (0);
		cmd->redir = cmd->redir->next;
	}
	cmd->redir = head;
	return (1);
}

int	redir_no_file_checker(t_cmd **cmds)
{
	t_cmd	*head;

	head = (*cmds);
	while (*cmds)
	{
		if (!has_file(*cmds))
			return (0);
		(*cmds) = (*cmds)->next;
	}
	(*cmds) = head;
	return (1);
}
