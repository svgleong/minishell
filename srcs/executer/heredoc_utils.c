/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:41:17 by svalente          #+#    #+#             */
/*   Updated: 2023/11/14 12:07:09 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	heredoc_error(char *del)
{
	printf("\nWarning: heredoc delimited by EOF (wanted: \"%s\")\n", del);
}

void	handle_c(int signal)
{
	if (signal == SIGINT)
	{
		write(2, "\n ", 1);
		general_free(data()->pointer_cmd, 1, 1, 0);
		close(data()->here[0]);
		close(data()->here[1]);
		data()->exit = 130;
		exit(data()->exit);
	}
}

int	check_quotes_here(char *s)
{
	int	i;
	int	j;
	int	flag;

	i = -1;
	j = 0;
	flag = 0;
	while (s[++i] && flag == 0)
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			j = i + 1;
			while (s[j])
			{
				if (s[j] == '\'' || s[j] == '\"')
				{
					flag = 1;
					break ;
				}
				j++;
			}
		}
	}
	return (flag);
}

void	remove_quotes_here(char *str)
{
	int	len;
	int	i;
	int	j;

	i = 0;
	j = 0;
	len = strlen(str);
	while (i < len)
	{
		if ((str[i] == '\'' && str[i + 1] == '\"') \
			|| (str[i] == '\"' && str[i + 1] == '\''))
			i += 2;
		else if (str[i] == '\'' || str[i] == '\"')
			i++;
		str[j++] = str[i++];
	}
	str[j] = '\0';
}
