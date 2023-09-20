/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 16:40:58 by svalente          #+#    #+#             */
/*   Updated: 2022/11/02 18:54:29 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}

/* #include <string.h>
#include <stdio.h>
int main()
{
    char s2[] = {0, 0, 42, 0};
	char s3[] = {0, 0, 42, 0};
    printf("Original: %d \n", memcmp(s2, s3, 4));
    printf("Mine: %d \n", ft_memcmp(s2, s3, 4));
} */