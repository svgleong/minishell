/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:40:47 by svalente          #+#    #+#             */
/*   Updated: 2023/10/09 15:26:28 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

int	valid_quotes(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			if (skip_quotes(str, '\'', &i) == -1)
				return (0);
		}
		else if (str[i] == '"')
		{
			if (skip_quotes(str, '"', &i) == -1)
				return (0);
		}
	}
	return (1);
}

int	valid(char *str, char delim, char opps)
{
	int	i;
	int	ct;

	i = 0;
	ct = 1;
	if (!str || !str[0])
		return (0);
	if (delim != '|' && str[0] == delim && ++i)
		ct++;
	while (str[i])
	{
		if (ct == 2 && str[i] == delim)
			return (0);
		else if (!is_special_char(str[i]) && !ft_isspace(str[i]))
			return (1);
		else if (ct == 1 && str[i] == delim)
			return (0);
		else if (str[i] == opps || str[i] == delim)
			return (0);
		else if (delim == '|' && (str[i] == '<' || str[i] == '>'))
			return (1);
		else if (is_special_char(str[i]))
			return (0);
		i++;
	}
	return (0);
}

int	valid_delimiters(char *str)
{
	int		i;
	bool	del;

	i = -1;
	del = true;
	if (str[0] == '|')
		return (false);
	while (str[++i])
	{
		if (str[i] == '\'')
			if (skip_quotes(str, '\'', &i) == -1)
				del = false;
		if (str[i] == '"')
			if (skip_quotes(str, '"', &i) == -1)
				del = false;
		if (str[i] == '>')
			del = valid(str + i + 1, '>', '<');
		else if (str[i] == '<')
			del = valid(str + i + 1, '<', '>');
		else if (str[i] == '|')
			del = valid(str + i + 1, '|', '|');
		if (del == false)
			break ;
	}
	return (del);
}

int	checker(char *rl)
{
    if (!valid_quotes(rl))
    {
		printf("Invalid quotes\n");
		free (rl);
		return (0);
    }
	if (!valid_delimiters(rl))
	{
		printf("syntax error near unexpected token\n");
		free (rl);
		return (0);
    }
	return (1);
}
