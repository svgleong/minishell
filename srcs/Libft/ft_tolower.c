/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 13:10:46 by svalente          #+#    #+#             */
/*   Updated: 2022/11/02 18:57:50 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c += 32;
	return (c);
}

/* #include <ctype.h>
#include <stdio.h>

int	main()
{
	int	c;

	c = 'A';
	printf("original = %i\n", c);
	printf("tranformeidrieds = %i\n", ft_tolower(c));
} */