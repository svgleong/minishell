/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com >  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:16:47 by svalente          #+#    #+#             */
/*   Updated: 2022/11/16 18:17:45 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_count_words(const char *s, char c)
{
	size_t	count;
	int		boolean;

	count = 0;
	boolean = 0;
	while (*s)
	{
		if (*s != c && boolean == 0)
		{
			boolean = 1;
			count++;
		}
		else if (*s == c)
			boolean = 0;
		s++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	char	**split;
	int		index;

	split = malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (!s || !split)
		return (0);
	i = 0;
	j = 0;
	index = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			split[j++] = ft_substr(s, index, i - index);
			index = -1;
		}
		i++;
	}
	split[j] = 0;
	return (split);
}

/* 
#include <stdio.h>
int	main()
{
	char *s = " ola eu    sou a sofia";
	char c = ' ';

	printf("%s-%s\n", ft_split(s, c));
} */