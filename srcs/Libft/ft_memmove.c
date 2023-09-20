/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com >  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 16:07:04 by svalente          #+#    #+#             */
/*   Updated: 2022/11/17 11:58:02 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (0);
	if (src < dest)
	{
		while (n > 0)
		{
			n--;
			((unsigned char *)dest)[n] = ((unsigned char *)src)[n];
		}
	}
	else
	{
		while (i < n)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	return (dest);
}

/* #include <string.h>
#include <stdio.h>

int	main()
{
	const char str1[] = "a sofia idiotaaaaaaaaaaaaaaaaaaaaaaa";
	char str2[] = "o rodri";
	
	printf("dest_unmodified = %s\n", str2);
	memmove(str2, str1, 13);
	printf("des_modified = %s\n", str2);
} */