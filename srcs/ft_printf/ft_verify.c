/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verify.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com >  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 11:50:12 by svalente          #+#    #+#             */
/*   Updated: 2023/09/01 10:17:01 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_verify(const char letter, va_list args)
{
	if (letter == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (letter == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (letter == 'p')
		return (ft_putnbrpointer(HEX_LOW_BASE, va_arg(args, unsigned long), 0));
	else if (letter == 'd' || letter == 'i')
		return (ft_putnbrbase(DEC_BASE, va_arg(args, int)));
	else if (letter == 'u')
		return (ft_putnbrbase(DEC_BASE, va_arg(args, unsigned int)));
	else if (letter == 'x')
		return (ft_putnbrbase(HEX_LOW_BASE, va_arg(args, unsigned int)));
	else if (letter == 'X')
		return (ft_putnbrbase(HEX_UP_BASE, va_arg(args, unsigned int)));
	else if (letter == '%')
		return (ft_putchar('%'));
	return (0);
}
