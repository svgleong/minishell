/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:47:32 by svalente          #+#    #+#             */
/*   Updated: 2022/11/03 17:57:52 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}

/* #include <stdio.h>
#include <ctype.h>

int	main()
{
	int n = 23456789;

	printf("%i\n", ft_isascii(n));
	printf("Real = %i\n", isascii(n));
} */