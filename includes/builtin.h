/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:42:32 by svalente          #+#    #+#             */
/*   Updated: 2023/11/13 19:47:18 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <cmd.h>

typedef struct s_env
{
	char			*content;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

t_env	*env(void);
void	free_env_list(t_env **lst);
void	bubble_sort(char **matrix);
void	print_export(char **export_env);
char	*get_env_var(char *str);
t_env	*env_new_node(char *str);
void	env_add_node_end(t_env *lst, t_env *new);
t_env	*search_env(char *var);
void	exitbuiltin(int i);
void	simple_env(void);
void	env_checker(char **env);
void	handle_c(int signal);
int		check_quotes_here(char *s);
void	heredoc_error(char *del);
void	remove_quotes_here(char *str);

#endif