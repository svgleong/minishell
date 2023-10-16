/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 21:28:12 by svalente          #+#    #+#             */
/*   Updated: 2023/10/14 22:14:12 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	redirections(t_cmd **cmds)
{
	t_cmd	*tmp_cmds;
	t_redir	*tmp_redir;

	tmp_cmds = *cmds;
	tmp_redir = tmp_cmds->redir;
	while (*cmds)
	{
		if ((*cmds)->redir)
		{
			if ((*cmds)->redir == 4 && (*cmds)->fd_in == -1)
			{
				(*cmds)->fd_in = open((*cmds)->redir->file, O_RDONLY);
				if ((*cmds)->fd_in == -1)
					printf("Error opening file\n");
			}
			// else if ((*cmds)->redir == 3)
			// {
			// 	(*cmds)->fd_out = open((*cmds)->redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			// 	if ((*cmds)->fd_out == -1)
			// 		printf("Error opening file\n");
			// }
			// else if ((*cmds)->redir == 1)
			// {
			// 	(*cmds)->fd_out = open((*cmds)->redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			// 	if ((*cmds)->fd_out == -1)
			// 		printf("Error opening file\n");
			// }
			// else if ((*cmds)->redir == 2)
			// {
			// 	(*cmds)->fd_in = open((*cmds)->redir->file, O_RDONLY);
			// 	if ((*cmds)->fd_in == -1)
			// 		printf("Error opening file\n");
			// }
		}
	}
}

void	redir_output(t_cmd **cmds)
{
	t_redir	*last_node;
	t_cmd	*tmp_cmds;
	
	tmp_cmds = *cmds;
	
}