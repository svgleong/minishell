/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 10:08:22 by svalente          #+#    #+#             */
/*   Updated: 2023/09/25 16:18:49 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**free_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return (NULL);
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
	return (NULL);
}
