/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com >  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:58:23 by svalente          #+#    #+#             */
/*   Updated: 2022/11/09 12:13:16 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(src);
	if (!dst || !src)
		return (0);
	if (size == 0)
		return (len);
	while (i < size - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (len);
}

/* #include <string.h>
#include <stdio.h>
#include <stdlib.h>

int	main()
{
	char	*dst;
	char	src[] = "ola";
	char	trash[] = "---------------------------------------";

	dst = malloc(sizeof(char) * (strlen(trash) + 1));
	if (!dst)
		return (0);
	ft_strlcpy(dst, trash, 30);
	printf("antes  = %s\n", dst);
	ft_strlcpy(dst, src, 30);
	printf("depois = %s\n", dst);
	free(dst);
} */