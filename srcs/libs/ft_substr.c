/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 18:34:15 by svalente          #+#    #+#             */
/*   Updated: 2023/11/14 12:50:25 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	if (len >= ft_strlen(s))
		len = ft_strlen(s) - start;
	if (start >= ft_strlen(s))
		return (ft_calloc(1, 1));
	sub = ft_calloc(sizeof(char), len + 1);
	if (!sub)
		general_free(data()->pointer_cmd, 1, 0, 1);
	while (start < ft_strlen(s) && i < len)
		sub[i++] = s[start++];
	return (sub);
}
