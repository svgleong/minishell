/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com >  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 11:06:52 by svalente          #+#    #+#             */
/*   Updated: 2022/11/30 12:03:58 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *str, ...)
{
	int		i;
	va_list	list_args;
	int		len;

	i = 0;
	len = 0;
	va_start(list_args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			len += ft_verify(str[i + 1], list_args);
			i++;
		}
		else
			len += ft_putchar(str[i]);
		i++;
	}
	va_end(list_args);
	return (len);
}
