/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 17:43:07 by svalente          #+#    #+#             */
/*   Updated: 2023/11/13 19:18:24 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	calculate_result(char *str, char *value, int key, int i)
{
	int	size;

	size = i;
	size += ft_strlen(value) + (ft_strlen(str) - i - key);
	return (size);
}

char	*get_status(char *str, int *i)
{
	char	*new;
	char	*exit_code;

	exit_code = ft_itoa(data()->exit);
	new = expanding(str, exit_code, 1, *i);
	(*i) += ft_strlen(exit_code) - 1;
	free(exit_code);
	return (new);
}

char	*remove_expand(char *str, int *i)
{
	char	*new_str;
	int		key;

	key = key_value(ft_strchr(str + *i, '$'));
	new_str = expanding(str, "", key, *i);
	return (new_str);
}

char	*remove_dollar(char *str, int *cursor)
{
	char	*new_str;
	int		j;
	int		k;
	int		i;

	i = (*cursor);
	new_str = ft_calloc(sizeof(char), ft_strlen(str));
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
	(*cursor)--;
	return (new_str);
}

char	*remove_character(char *str, int *cursor)
{
	char	*new_str;

	new_str = expanding(str, "", 1, *cursor);
	(*cursor)--;
	return (new_str);
}
