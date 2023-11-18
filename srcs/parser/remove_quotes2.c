/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 16:01:47 by svalente          #+#    #+#             */
/*   Updated: 2023/11/18 16:02:20 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	quote_checker_file(t_cmd **cmd)
{
	t_cmd	*head;
	t_redir	*head_redir;

	head = *cmd;
	while (*cmd)
	{
		head_redir = (*cmd)->redir;
		while ((*cmd)->redir)
		{
			(*cmd)->redir->file = remove_quotes_redir((*cmd)->redir->file);
			(*cmd)->redir = (*cmd)->redir->next;
		}
		(*cmd)->redir = head_redir;
		(*cmd) = (*cmd)->next;
	}
	(*cmd) = head;
}

void	quote_checker(t_cmd **cmd)
{
	t_cmd	*head;

	head = *cmd;
	while (*cmd)
	{
		remove_quotes((*cmd)->args);
		(*cmd) = (*cmd)->next;
	}
	(*cmd) = head;
}
