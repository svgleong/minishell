/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 09:56:49 by svalente          #+#    #+#             */
/*   Updated: 2023/09/27 16:54:57 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <string.h>

int	redirections(t_cmd **lst)
{
	int		i;
	t_cmd	*tmp;
	int		fd;
	
	i = 0;
	tmp = *lst;
	//printf("debug\n");
	while ((*lst))
	{
		i = 0;
		while ((*lst)->args[i])
		{
			if (!ft_strncmp((*lst)->args[i], "<", 2) && (*lst)->args[i + 1])
			{
				//printf("debug1\n");
				(*lst)->redir = 1;
				fd = open((*lst)->args[i + 1], O_RDONLY);
				if (fd < 0)
				{
					printf("Error opening infile\n"); //MELHORAR
					break ;
				}
				(*lst)->fd_in = fd;
			}
			else if (!ft_strncmp((*lst)->args[i], ">", 2) && (*lst)->args[i + 1])
			{
				//printf("debug2\n");
				(*lst)->redir = 0;
				fd = open((*lst)->args[i + 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
				if (fd < 0)
				{
				 	printf("Error opening outfile\n"); //MELHORAR
					break ;	
				}
				(*lst)->fd_out = fd;
			}
			i++;
		}
		*lst = (*lst)->next;
	}
	(*lst) = tmp;
	return (0);
}