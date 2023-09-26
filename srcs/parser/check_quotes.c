/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:40:47 by svalente          #+#    #+#             */
/*   Updated: 2023/09/26 17:02:44 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int valid_quotes(char *str)
{
    int		i;
    char    quote;
	int		n_quote;
	int		len;

	i = 0;
	quote = '\0';
	n_quote = 0;
	while (str[i])
	{
		if (!quote && (str[i] == '\"' || str[i] == '\''))
		{
			quote = str[i++];
			n_quote++;
		}
		if (!str[i])
			break ;
		while (str[i] && quote && str[i] != quote)
			i++;
		if (str[i] && quote && str[i] == quote)
		{
			quote = '\0';
			n_quote++;
		}
		i++;
	}
	if (n_quote % 2 != 0)
	 	return (0);
	return (1);
}

int	valid_delimiters(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i++] == '|')
		{
			while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
				i++;
			if (str[i] == '|')
				return (0);
		}
		/* if (str[i++] == '>')
		{
			while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
				i++;
			if (!str[i] || )
		} */
			
	}
	return (1);
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