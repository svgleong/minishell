/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parallels <parallels@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 22:20:58 by svalente          #+#    #+#             */
/*   Updated: 2023/10/15 16:55:29 by parallels        ###   ########.fr       */
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
size_t	ft_strlen_special(const char *s, int i);
void	*ft_memset(void *s, int c, size_t n);
char	*ft_strdup(const char *s);
char	*ft_strdup_special(const char *s, int c);
char	*ft_strchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_isspace(char c);
int		is_special_char(char c);
int		valid_delimeters(char *str);
int		skip_quotes(char *str, char quote, int *i);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
void ft_putstr_fd(char *s, int fd);
void ft_putchar_fd(char c, int fd);



//added
void	ft_putendl_fd(char *s, int fd);
void *ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strjoin_free(char *s1, char *s2, int free_str);
char **env_to_matrix(void);
int	list_size(void);
int ft_strcmp(const char *s1, const char *s2);

#endif