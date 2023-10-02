/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:40:47 by svalente          #+#    #+#             */
/*   Updated: 2023/09/27 18:02:23 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	validate(char *str, char quote, int *i)
{
	if (!str[++(*i)])
		return -1;
	while (str[*i])
	{
		if (str[*i] == quote)
			return 1;
		(*i)++;
	}
	return (-1);
}

int	valid_quotes(char *str)
{
	int		i;
	bool	del;

	i = -1;
	del = true;
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			if (validate(str, '\'', &i) == -1)
				return 0;
		}
		else if (str[i] == '"')
		{
			if (validate(str, '"', &i) == -1)
				return 0;
		}
	}
	return 1;		
}

int	valid(char *str, char delim, char opps)
{
	int	i;
	int	ct;
	// Find an opposite redirection: < >
	// Find spaced redirections exampl: < <
	// Finds more than on red in the same scope: <<< or >>>
	// Stops when finds a normar character !is_special_char and ret true
	
	i = 0;
	ct = 1;
	if (!str || !str[0])
		return 0;
	if (str[0] == delim && ++i)
		ct++;
	//printf("str[0] :%c: e delim :%c:\n", str[0], delim);
	while (str[i])
	{
		if (ct == 2 && str[i] == delim)
			return 0;
		else if (!is_special_char(str[i]) && !ft_isspace(str[i]))
			return (1);
		else if (ct == 1 && str[i] == delim)
			return 0;
		else if (str[i] == opps)
			return 0;
		else if (is_special_char(str[i]))
			return (0);
		i++;
	}
	return (0);
}

int		valid_delimiters(char *str)
{
	int		i;
	bool	del;
	
	i = -1;
	del = true;
	while (str[++i])
	{
		if (str[i] == '>')
			del = valid(str + i + 1, '>', '<');
		else if (str[i] == '<')
			del = valid(str + i + 1, '<', '>');
		if (del == false)
			break ;
	}
	//printf("validate del: %d\n", del);
	return (del);
}

int   checker(char *rl)
{
    if (!valid_quotes(rl))
    {
        printf("Invalid quotes\n");
        free (rl);
		return (0);
    }
	if (!valid_delimiters(rl))
	{
        printf("Invalid delimiters\n");
        free (rl);
    	return (0);
    }
	return (1);
}