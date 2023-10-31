/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 21:28:12 by svalente          #+#    #+#             */
/*   Updated: 2023/10/31 14:03:54 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	redir_in(t_cmd **cmds);
static void	redir_out(t_cmd **cmds);
static void	redir_out_append(t_cmd **cmds);

void	redirections(t_cmd **cmds)
{
	t_cmd	*tmp_cmds;
	t_redir	*tmp_redir;


	
	tmp_cmds = *cmds;
	if (!tmp_cmds)
		return ;
	while (*cmds)
	{
		tmp_redir = tmp_cmds->redir;
		while ((*cmds)->redir)
		{
			if ((*cmds)->redir->redir == 4 && (*cmds)->fd_in == -1)
				redir_in(cmds);
			else if ((*cmds)->redir->redir == 3)
				redir_out(cmds);
			else if ((*cmds)->redir->redir == 1)
				redir_out_append(cmds);
			else if ((*cmds)->redir->redir == 2)
				(*cmds)->fd_in = heredoc(*cmds);
			(*cmds)->redir = (*cmds)->redir->next;
		}
		//print_redir((*cmds)->redir);
		(*cmds) = (*cmds)->next;
	}
	(*cmds) = tmp_cmds;
	(*cmds)->redir = tmp_redir;
}

static void	redir_in(t_cmd **cmds)
{
	//
	data()->redir = 1;
	//
	(*cmds)->fd_in = open((*cmds)->redir->file, O_RDONLY);
	if ((*cmds)->fd_in == -1)
		printf("Error opening file\n");
}

static void	redir_out(t_cmd **cmds)
{
	//
	data()->redir = 1;
	//
	if ((*cmds)->fd_out != -1)
		close((*cmds)->fd_out);
	(*cmds)->fd_out = open((*cmds)->redir->file, O_WRONLY | O_CREAT \
		| O_TRUNC, 0644);
	if ((*cmds)->fd_out == -1)
		printf("Error opening file\n");
}

static void	redir_out_append(t_cmd **cmds)
{
	//
	data()->redir = 1;
	//
	if ((*cmds)->fd_out != -1)
		close((*cmds)->fd_out);
	(*cmds)->fd_out = open((*cmds)->redir->file, O_WRONLY | O_CREAT \
		| O_APPEND, 0644);
	if ((*cmds)->fd_out == -1)
		printf("Error opening file\n");
}
