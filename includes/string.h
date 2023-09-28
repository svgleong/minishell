/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzarichn <mzarichn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 22:20:58 by svalente          #+#    #+#             */
/*   Updated: 2023/09/27 15:57:02 by mzarichn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_H
# define STRING_H

# include <stddef.h>
# include "alloc.h"
# include <stdlib.h>

char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *s, int c, size_t n);
char	*ft_strdup(const char *s);

#endif