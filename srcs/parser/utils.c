/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 09:52:09 by svalente          #+#    #+#             */
/*   Updated: 2023/09/25 11:34:31 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <string.h>

char **copy_matrix(char **matrix)
{
    char    **dup;
    int i;

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