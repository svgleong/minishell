/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com >  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 19:01:31 by svalente          #+#    #+#             */
/*   Updated: 2022/11/09 12:23:56 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*p;

	p = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		p[i] = c;
		i++;
	}
	return (p);
}

/* #include <string.h>
#include <stdio.h>

int	main()
{
	char	str[] = "222222222";

	printf("str = %s\n", str);
	printf("%p\n", ft_memset(&str, 'a', 0));
	printf("%p\n", memset(&str, '5', 1));
	printf("%p\n", str);
	printf("str = %s\n", str);
} */