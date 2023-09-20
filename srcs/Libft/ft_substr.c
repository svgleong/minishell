/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com >  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:14:19 by svalente          #+#    #+#             */
/*   Updated: 2022/11/16 16:59:47 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
		return (NULL);
	while (start < ft_strlen(s) && i < len)
		sub[i++] = s[start++];
	return (sub);
}

/* #include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	char *teste = "SofiaValenteGoncalvesLeong";
	printf("%s\n", ft_substr(teste, 500, 7));
	printf("%s\n", substr(teste, 500, 7));
}
 */