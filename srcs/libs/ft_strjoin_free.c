/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 18:29:05 by svalente          #+#    #+#             */
/*   Updated: 2023/11/14 14:49:40 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_strjoin_free(char *s1, char *s2, int free_str)
{
	char	*new_str;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)//|| !s1[0] || !s2[0])
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new_str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!new_str)
		general_free(data()->pointer_cmd, 1, 0, 1);
	ft_memcpy(new_str, s1, s1_len);
	ft_memcpy(new_str + s1_len, s2, s2_len);
	new_str[s1_len + s2_len] = '\0';
	if (free_str == 1 || free_str == 3)
		free(s1);
	if (free_str == 2 || free_str == 3)
		free(s2);
	return (new_str);
}
