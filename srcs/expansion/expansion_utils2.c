/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:20:28 by svalente          #+#    #+#             */
/*   Updated: 2023/10/09 12:20:49 by svalente         ###   ########.fr       */
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
