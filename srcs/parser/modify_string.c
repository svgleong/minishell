/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 15:21:53 by svalente          #+#    #+#             */
/*   Updated: 2023/10/07 11:39:39 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <string.h>

static int  count_delimiter(char *rl)
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

static int  add_delimiter(char **rl, char *str, int *j, char quote)
{
    int count;

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

char *modify_str(char *rl)
{
    char    quote;
    char    *str;
    int     j;

    quote = '\0';
    str = malloc(ft_strlen(rl) * 5);
    j = 0;
    while (*rl)
    {
        if (!quote && (*rl == '\"' || *rl == '\''))
        {    
            str[j++] = '\2';
            quote = *rl;
        }
        else if (quote && quote == *rl)
        {
            str[j++] = *rl++;
            str[j++] = '\2';
            quote = '\0';
            continue ;
        }
        if (add_delimiter(&rl, str, &j, quote))
            continue ;
        if (!quote && *rl == ' ')
            *rl = '\2';
        str[j++] = *rl++;
    }
    str[j] = '\0';
	// printf("MODIFIED: %s\n", str);
    return (str);
}

char	**separate_args(char *rl)
{
	char	*mod_str;
	char	**all_args;
	//int		i;

	mod_str = modify_str(rl);
	all_args = ft_split(mod_str, '\2');
	//i = -1;
	// while (all_args && all_args[++i])
	// 	printf("ARG[%i]: %s\n", i, all_args[i]);
	free(rl);
	free(mod_str);
	return (all_args);
}
