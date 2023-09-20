/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:23:06 by svalente          #+#    #+#             */
/*   Updated: 2022/11/02 18:53:36 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/* #include <stdio.h>
#include <ctype.h>

int	main()
{
	int	letra;

	letra = 64;
	printf("Fake - %i\n", ft_isalpha(letra));
	printf("Real = %i\n", isalpha(letra));
	letra = 'a';
	printf("Fake - %i\n", ft_isalpha(letra));
	printf("Real = %i\n", isalpha(letra));
	letra = 13;
	printf("Fake - %i\n", ft_isalpha(letra));
	printf("Real = %i\n", isalpha(letra));

}
 */