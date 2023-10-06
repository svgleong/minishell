/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 17:43:07 by svalente          #+#    #+#             */
/*   Updated: 2023/10/06 17:47:45 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	calculate_result(char *str , char *value, int key)
{
	if (!value)
		return (ft_strlen_special(str, '$') + ft_strlen(ft_strchr(str, '$') \
		+ key));
	return (ft_strlen_special(str, '$') + ft_strlen(value) + \
	ft_strlen(ft_strchr(str, '$') + key));
}

char	*get_status(char *str, int i)
{
	(void)str;
	(void)i;
	return NULL;
}

char	*remove_expand(char *str)
{
	char	*new_str;
	int		sz;
	int		key;
	int		i;
	
	key = key_value(ft_strchr(str, '$'));
	sz = calculate_result(str, NULL, key);
	new_str = malloc(sz);
	sz = -1;
	while (str[++sz] && str[sz] != '$')
		new_str[sz] = str[sz];
	i = sz + key + 1;
	while (str[i])
	{
		new_str[sz++] = str[i];
		i++;
	}
	new_str[sz] = '\0';
	return (new_str);
}

char	*remove_dollar(char *str, int i)
{
	char	*new_str;
	int		j;
	int		k;

	new_str = malloc(ft_strlen(str));
	j = -1;
	k = 0;
	while (str[++j])
	{
		if (j == i)
			j++;
		new_str[k] = str[j];
		k++;
	}
	new_str[k] = '\0';
	return (new_str);
}

char	*remove_number(char *str, int i)
{
	char	*new_str;
	int		j;
	int		k;
	
	new_str = malloc(ft_strlen(str) - 1);
	j = -1;
	k = 0;
	while (str[++j])
	{
		if (j == i)
			j += 2;
		new_str[k] = str[j];
		k++;
	}
	new_str[k] = '\0';
	return (new_str);
}
