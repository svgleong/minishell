/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 21:05:47 by svalente          #+#    #+#             */
/*   Updated: 2023/11/14 22:01:34 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include <builtin.h>
# include <minishell.h>
# include <string_lib.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>

char	*ft_strdup(const char *s);
void	env_bi(char **env, t_env *env_lst);
t_env	*env(void);
void	get_env_to_list(char **env);
void	echo_bi(t_cmd *cmd);
void	only_export(void);
int		can_execute_command(char *command);
void	execution(t_cmd *cmd);
char	*find_command_path(char *command);
void	exec_error(char *cmd, char *s, int exit_code);
void	heredoc_exception(t_cmd *cmd);

#endif