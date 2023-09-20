/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:35:12 by svalente          #+#    #+#             */
/*   Updated: 2022/11/02 18:57:02 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;
	int		i;

	i = 0;
	s2 = malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!s2)
		return (NULL);
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

/* #include <stdio.h>
#include <string.h>

int	main(int ac, char **av)
{
	char	*mine;
	char	*real;
	
	if (ac == 2)
	{
		mine = ft_strdup(av[1]);
		real = strdup(av[1]);
		printf("mine:%s:\nreal:%s:\n", mine, real);
	}
	return (0);
}

int	main(void)
{
	char *test;
	char *dup;
	test = "Testando a função strdup!";
	printf("test = %s\n", test);
	dup = ft_strdup(test);
	printf("dup  = %s\n", dup);
	free(dup);
} */