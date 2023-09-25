/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:40:47 by svalente          #+#    #+#             */
/*   Updated: 2023/09/25 15:10:05 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int valid_quotes(char *str)
{
    int i;
    int d_quotes;
    int s_quotes;

    i = 0;
    d_quotes = 0;
    s_quotes = 0;
    while(str[i])
    {
        if (str[i] == '\"')
            d_quotes++;
        if (str[i] == '\'')
            s_quotes++;
        i++;
    }
    if (d_quotes % 2 == 0 && s_quotes % 2 == 0)
        return (1);
    return (0);
}

void    check_quotes(char *rl)
{
    if (!valid_quotes(rl))
    {
        printf("Invalid quotes");
        free (rl);
        exit(EXIT_FAILURE);
    }
}