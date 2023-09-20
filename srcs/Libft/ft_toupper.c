/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 12:29:53 by svalente          #+#    #+#             */
/*   Updated: 2022/11/02 18:57:55 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c -= 32;
	return (c);
}

/* #include <ctype.h>
#include <stdio.h>

int	main()
{
	int	c;

	c = 'a';
	printf("original = %i\n", c);
	printf("tranformeidrieds = %i\n", ft_toupper(c));
} */