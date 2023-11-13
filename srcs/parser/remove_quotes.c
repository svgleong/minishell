/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:41:19 by svalente          #+#    #+#             */
/*   Updated: 2023/11/12 14:52:44 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*rem_quotes_pair(char *arg, char quote, int *j)
{
	char	*new_str;
	int		i;
	int		tmp;

	i = -1;
	new_str = malloc(ft_strlen(arg) - 1);
	while (++i < *j)
		new_str[i] = arg[i];
	(*j)++;
	while (arg[(*j)] != quote)
	{
		new_str[i] = arg[(*j)];
		(*j)++;
		i++;
	}
	tmp = (*j);
	while (++tmp < (int)ft_strlen(arg))
	{
		new_str[i] = arg[tmp];
		i++;
	}
	(*j) = (*j) - 2;
	new_str[i] = '\0';
	free(arg);
	return (new_str);
}

void	remove_quotes(char **args)
{
	int		i;
	int		j;

	i = -1;
	while (args[++i])
	{
		j = -1;
		while (args[i][++j])
		{
			if (args[i][j + 1] && args[i][j] == '<' && args[i][j + 1] == '<' )
			{
				i++;
				break ;
			}
			else if (args[i][j] == '\'')
				args[i] = rem_quotes_pair(args[i], '\'', &j);
			else if (args[i][j] == '"')
				args[i] = rem_quotes_pair(args[i], '"', &j);
			if (j >= (int)ft_strlen(args[i]))
				break ;
		}
	}
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
