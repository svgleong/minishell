/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 12:06:45 by svalente          #+#    #+#             */
/*   Updated: 2023/07/26 10:41:23 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
	{
		ft_putstr("(null)");
		return (6);
	}
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
	return (i);
}

size_t	ft_strlen_printf(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_putnbrbase(char *base, long long nb)
{
	long long	len;
	int			count;

	count = 0;
	len = ft_strlen_printf(base);
	if (nb < 0)
	{
		ft_putchar('-');
		nb *= -1;
		count++;
	}
	if (nb >= len)
		count += ft_putnbrbase(base, nb / len);
	return (count += ft_putchar(base[nb % len]));
}

int	ft_putnbrpointer(char *base, unsigned long nb, int checker)
{
	int	count;
	int	len;

	count = 0;
	len = ft_strlen_printf(base);
	if (!nb)
		return (ft_putstr("(nil)"));
	if (checker == 0)
		count = ft_putstr("0x");
	if (nb >= (unsigned long)len)
		count += ft_putnbrpointer(base, nb / len, 1);
	return (count += ft_putchar(base[nb % len]));
}
