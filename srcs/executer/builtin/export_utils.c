/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:41:17 by svalente          #+#    #+#             */
/*   Updated: 2023/11/13 21:06:35 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_env_var(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != '=')
		i++;
	return (ft_substr(str, 0, i));
}

void	print_export(char **export_env)
{
	char	*temp;
	int		i;
	int		j;

	i = -1;
	while (export_env[++i])
	{
		if (!ft_strncmp(export_env[i], "_=", 2))
			continue ;
		temp = get_env_var(export_env[i]);
		printf("declare -x %s", temp);
		j = 0;
		while (temp[j])
			j++;
		if (export_env[i][j] == '=')
			printf("=\"%s\"\n", &export_env[i][j + 1]);
		else
			printf("\n");
		free(temp);
	}
}

void	bubble_sort(char **matrix)
{
	int		i;
	int		j;
	char	*temp;
	int		size;

	size = 0;
	while (matrix[size])
		size++;
	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp(matrix[j], matrix[j + 1]) > 0)
			{
				temp = matrix[j];
				matrix[j] = matrix[j + 1];
				matrix[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

int	is_valid(char *var)
{
	int	i;

	i = 0;
	if (!var[0])
		return (0);
	if (ft_isdigit(var[i]) || var[0] == '_' || var[0] == '=')
		return (0);
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) || var[i] == '_')
			return (0);
		i++;
	}
	return (1);
}

char	*rem_quotes_export(char *s)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = malloc(sizeof(char) * ft_strlen(s) + 1);
	while (s[i])
	{
		if (s[i] != '\"')
		{
			new[j] = s[i];
			j++;
		}
		i++;
	}
	new[j] = '\0';
	return (new);
}
