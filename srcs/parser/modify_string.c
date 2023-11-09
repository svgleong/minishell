/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 15:21:53 by svalente          #+#    #+#             */
/*   Updated: 2023/11/08 16:56:09 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	count_delimiter(char *rl)
{
	if (!rl || rl[0] == '\0')
		return (0);
	if (*rl == '|')
		return (1);
	if (rl[0] == '>' && rl[1] == '>')
		return (2);
	if (rl[0] == '<' && rl[1] == '<')
		return (2);
	if (*rl == '>')
		return (1);
	if (*rl == '<')
		return (1);
	return (0);
}

static int	add_delimiter(char **rl, char *str, int *j, char quote)
{
	int	count;

	count = count_delimiter(*rl);
	if (quote || (!quote && *rl && !count))
		return (0);
	str[(*j)++] = '\2';
	str[(*j)++] = *rl[0]++;
	if (count == 2)
		str[(*j)++] = *rl[0]++;
	str[(*j)++] = '\2';
	return (1);
}

void	modify_str_aux(char *str, char *quote, char **rl, int *j)
{
	(void)str;
	(void)j;
	if (!quote[0] && (**rl == '\"' || **rl == '\''))
	{
		quote[0] = *rl[0];
	}
	else if (*quote && *quote == **rl)
		quote[0] = '\0';
}

char	*modify_str(char *rl)
{
	char	quote;
	char	*str;
	int		j;

	quote = '\0';
	if (!rl || !rl[0])
		return (NULL);
	str = malloc(ft_strlen(rl) * 5);
	j = 0;
	while (*rl)
	{
		modify_str_aux(str, &quote, &rl, &j);
		if (!quote)
		{
			if (add_delimiter(&rl, str, &j, quote))
				continue ;
			if ((*rl == ' ' || *rl == '\t'))
				*rl = '\2';
		}
		str[j++] = *rl++;
	}
	str[j] = '\0';
	return (str);
}

char	**separate_args(char *rl)
{
	char	*mod_str;
	char	**all_args;

	mod_str = modify_str(rl);
	all_args = ft_split(mod_str, '\2');
	free(rl);
	free(mod_str);
	return (all_args);
}
