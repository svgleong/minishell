/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:41:19 by svalente          #+#    #+#             */
/*   Updated: 2023/11/18 16:02:24 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*allocate_new_str(char *arg)
{
	char	*new_str;

	new_str = ft_calloc(sizeof(char), ft_strlen(arg) - 1);
	if (!new_str)
		general_free(data()->pointer_cmd, 1, 0, 1);
	return (new_str);
}

char	*rem_quotes_pair(char *arg, char quote, int *j)
{
	char	*new_str;
	int		i;
	int		tmp;

	i = -1;
	new_str = allocate_new_str(arg);
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

char	*remove_quotes_redir(char *args)
{
	int		j;

	j = -1;
	while (args[++j])
	{
		if (args[j] == '\'')
			args = rem_quotes_pair(args, '\'', &j);
		else if (args[j] == '"')
			args = rem_quotes_pair(args, '"', &j);
	}
	return (args);
}

int	skip_quotes(char *str, char quote, int *i)
{
	if (!str[++(*i)])
		return (-1);
	while (str[*i])
	{
		if (str[*i] == quote)
			return (1);
		(*i)++;
	}
	return (-1);
}
