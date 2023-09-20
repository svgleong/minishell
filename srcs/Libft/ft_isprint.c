/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:55:32 by svalente          #+#    #+#             */
/*   Updated: 2022/11/02 18:54:13 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	if (c >= 32 && c < 127)
		return (1);
	return (0);
}

/* #include <stdio.h>
#include <ctype.h>

int	main()
{
	int n = 127;

	printf("%i\n", ft_isprint(n));
	printf("Real = %i\n", isprint(n));
} */