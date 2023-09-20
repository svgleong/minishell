/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com >  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:38:33 by svalente          #+#    #+#             */
/*   Updated: 2022/11/09 15:59:31 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	if (size <= ft_strlen(dst))
		return (size + ft_strlen(src));
	i = 0;
	j = ft_strlen(dst);
	while (src[i] && j < size - 1)
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	dst[j] = '\0';
	return (ft_strlen(dst) + ft_strlen(&src[i]));
}

/* ft_strlen(dst) + ft_strlen(&src[d])

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	c;
	size_t	d;

	if (dstsize <= ft_strlen(dst))
		return (dstsize + ft_strlen(src));
	c = ft_strlen(dst);
	d = 0;
	while (src[d] != '\0' && c + 1 < dstsize)
	{
		dst[c] = src[d];
		c++;
		d++;
	}
	dst[c] = '\0';
	return ();
}

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int	main()
{
	char	*dst;
	char	*src;

	src = malloc(sizeof(char) * (ft_strlen("adeus--") + 1));
	dst = malloc(sizeof(char) * (ft_strlen("adeus--") + ft_strlen("ola") + 1));
	ft_memmove(src, "adeus--", ft_strlen("adeus--"));
	ft_memmove(dst, "ola", ft_strlen("ola"));
	printf("antes  = [%s]\n", dst);
	ft_strlcat(dst, src, 12);
	printf("depois = [%s]\n", dst);
}
 */
// int main()
// {
// 	char	dest[14] = 'a';
// }