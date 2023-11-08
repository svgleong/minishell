/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:49:01 by svalente          #+#    #+#             */
/*   Updated: 2023/11/08 16:49:11 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_size_sign_0(int n)
{
	int	size;

	size = 0;
	if (n > 0)
		size = 0;
	else
		size = 1;
	return (size);
}

int	ft_sign(int n)
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

	nbr = (long)n * ft_sign(n);
	size = ft_size_sign_0(n);
	while (n != 0)
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
		str[size] = '0';
	else if (size == 0 && str[1] != '\0')
		str[size] = '-';
	return (str);
}
