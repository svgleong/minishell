/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 18:23:02 by svalente          #+#    #+#             */
/*   Updated: 2023/10/17 18:30:26 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (0);
	while (n > 0)
	{
		((char *)dest)[i] = ((const char *)src)[i];
		i++;
		n--;
	}
	return (dest);
}

/* void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*csrc;
	char	*cdest;

	csrc = (char *)src;
	cdest = (char *)dest;
	for (size_t i = 0; i < n; i++)
		cdest[i] = csrc[i];
	return dest;
} */