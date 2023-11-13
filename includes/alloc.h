/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 22:20:58 by svalente          #+#    #+#             */
/*   Updated: 2023/11/13 19:45:58 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOC_H
# define ALLOC_H

# include <stddef.h>

void	*ft_calloc(size_t count, size_t size);
char	**free_matrix(char **matrix);
char	**copy_matrix(char **matrix);
char	**copy_args(char **matrix);
char	**copy_args_until(char **matrix, char c, char d);
void	print_matrix(char **m);

#endif