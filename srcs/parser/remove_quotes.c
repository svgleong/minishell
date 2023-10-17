/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:41:19 by svalente          #+#    #+#             */
/*   Updated: 2023/10/17 17:43:18 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	remove_quotes(t_cmd **cmds)
{
	char	*tmp;
	int		i;
	t_cmd	*head;
	
	tmp = NULL;
	head = *cmds;
	while ((*cmds))
	{
		i = -1;
		while ((*cmds)->args[++i])
		{
			if ((*cmds)->args[i][0] == '\'' || (*cmds)->args[i][0] == '\"')
			{
				tmp = ft_substr((*cmds)->args[i], 1, ft_strlen((*cmds)->args[i]) - 2);
				free((*cmds)->args[i]);
				(*cmds)->args[i] = tmp;
			}
		}
		(*cmds) = (*cmds)->next;
	}
	(*cmds) = head;
	//printf("REMOVED QUOTES\n");
	//print_list(*cmds);
}