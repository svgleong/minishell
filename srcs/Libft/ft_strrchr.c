/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com >  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 15:11:56 by svalente          #+#    #+#             */
/*   Updated: 2023/09/01 10:09:35 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	len;

	len = ft_strlen(s);
	if (!s || !s[0])
		return (NULL);
	if ((unsigned char)c == '\0')
		return ((char *)s + len);
	while (len >= 0)
	{
		if (s[len] == (unsigned char)c)
			return ((char *)s + len);
		len--;
	}
	return (NULL);
}

/* #include <string.h>
#include <stdio.h>

int	main()
{
	char	*string = "Ola eu sou a Sofia.";
	char	*last = ft_strrchr(string, 'a');

	printf("last:%s\n", last);
	
	if(last == NULL)
		printf("Not found\n");
} */