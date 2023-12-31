/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:20:28 by svalente          #+#    #+#             */
/*   Updated: 2023/11/08 16:39:55 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	key_value(char *str)
{
	int	sz;

	sz = 0;
	while (str[++sz] && (ft_isalnum(str[sz]) || str[sz] == '_'))
		;
	return (sz -1);
}

void	ft_swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

char	**remove_str(char **args)
{
	int		i;
	int		j;
	char	**new_matrix;

	i = -1;
	while (args[++i])
	{
		j = i + 1;
		while (args[j])
		{
			if (args[i][0] == '\0')
				ft_swap(&args[i], &args[j]);
			j++;
		}
	}
	new_matrix = copy_args_until(args, '\0', '\0');
	free_matrix(args);
	return (new_matrix);
}

int	remove_empty_strs(t_cmd **cmds)
{
	t_cmd	*head;
	int		i;

	head = (*cmds);
	while (*cmds)
	{
		i = -1;
		while ((*cmds)->args[++i])
		{
			if ((*cmds)->args[i][0] == '>' || (*cmds)->args[i][0] == '<')
				if ((*cmds)->args[i + 1] && !(*cmds)->args[i + 1][0])
					return (0);
		}
		(*cmds) = (*cmds)->next;
	}
	(*cmds) = head;
	while (*cmds)
	{
		(*cmds)->args = remove_str((*cmds)->args);
		(*cmds) = (*cmds)->next;
	}
	(*cmds) = head;
	return (1);
}
