/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:20:28 by svalente          #+#    #+#             */
/*   Updated: 2023/10/17 14:35:42 by svalente         ###   ########.fr       */
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

char **remove_empty(char **args)
{
	int	i;

	i = -1;
	while (args[++i])
	{
		if (args[i][0] == '\0')
			printf("Todo la dentro\n");
	}
	return (NULL);
}