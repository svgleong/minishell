/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com >  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 20:00:36 by svalente          #+#    #+#             */
/*   Updated: 2022/11/17 14:36:02 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_size(int n)
{
	int	size;

	size = 0;
	if (n > 0)
		size = 0;
	else
		size = 1;
	return (size);
}

int	ft_sinal(int n)
{
	int	sinal;

	sinal = 0;
	if (n < 0)
		sinal = -1;
	else
		sinal = 1;
	return (sinal);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	nbr;
	size_t	size;

	nbr = (long)n * ft_sinal(n);
	size = ft_size(n);
	while (n)
	{
		n /= 10;
		size++;
	}
	str = (char *)malloc(size + 1);
	if (!str)
		return (0);
	str[size--] = '\0';
	while (nbr > 0)
	{
		str[size--] = nbr % 10 + '0';
		nbr /= 10;
	}
	if (size == 0 && str[1] == '\0')
		str[0] = '0';
	else if (size == 0 && str[1] != '\0')
		str[size] = '-';
	return (str);
}

/* #include <stdio.h>
int main()
{
	printf("Numero  256: %s \n", ft_itoa(256));
	printf("Numero -256: %s \n", ft_itoa(-256));
} */