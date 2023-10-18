/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 09:52:09 by svalente          #+#    #+#             */
/*   Updated: 2023/10/18 09:54:34 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <string.h>

char	**copy_matrix(char **matrix)
{
	char	**dup;
	int		i;

	i = 0;
	while (matrix[i] && matrix[i][0] != '|')
		i++;
	dup = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (matrix[i] && matrix[i][0] != '|')
	{
		dup[i] = ft_strdup(matrix[i]);
		if (dup[i] == NULL)
		{
			free_matrix(dup);
			printf("Error copying matrix\n"); //melhorar
			return (NULL);
		}
		i++;
	}
	return (dup);
}

char	**copy_args_until(char **matrix, char c, char d)
{
	char	**dup;
	int		i;

	i = 0;
	while (matrix[i] && matrix[i][0] != c && matrix[i][0] != d)
		i++;
	dup = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (matrix[i] && matrix[i][0] != c && matrix[i][0] != d)
	{
		dup[i] = ft_strdup(matrix[i]);
		if (dup[i] == NULL)
		{
			free_matrix(dup);
			printf("Error copying matrix\n"); //melhorar
			return (NULL);
		}
		i++;
	}
	matrix[i] = NULL;
	return (dup);
}

char	**copy_args(char **matrix)
{
	char	**dup;
	int		i;

	i = 0;
	while (matrix[i])
		i++;
	dup = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (matrix[i])
	{
		dup[i] = ft_strdup(matrix[i]);
		if (dup[i] == NULL)
		{
			free_matrix(dup);
			printf("Error copying matrix\n"); //melhorar
			return (NULL);
		}
		i++;
	}
	return (dup);
}

void	print_matrix(char **m)
{
	int i = 0;
	
	if(!m)
		return ;
	printf("PRINT MATRIX\n");
	while (m[i])
	{
		printf("[%s]\n", m[i]);
		i++;
	}
	printf("\n");
}
