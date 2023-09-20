/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 15:48:43 by svalente          #+#    #+#             */
/*   Updated: 2022/11/03 17:58:57 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*(const unsigned char *)(s + i) == (unsigned char)c)
			return ((unsigned char *)(s + i));
		i++;
	}
	return (NULL);
}

/* #include <string.h>
#include <stdio.h>

int	main()
{
	char	*string = "Ola eu sou a Sofia.";
	char	*first = ft_memchr(string, 'a', 2);

	printf("first:%s\n", first);
	
	if(first == NULL)
		printf("Not found\n");
} */