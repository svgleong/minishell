/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:43:20 by svalente          #+#    #+#             */
/*   Updated: 2023/11/18 16:01:03 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 25
# endif

# include <alloc.h>
# include <termios.h>
# include <cmd.h>
# include <string.h>
# include <string_lib.h>
# include <parser.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>
# include <signal.h>
# include <unistd.h>
# include <builtin.h>
# include <sys/wait.h>
# include <errno.h>
# include <limits.h>
# include <executer.h>

char	*get_next_line(int fd);
char	*find_command_path(char *command);
int		which_builtin(t_cmd *cmd);
int		cmd_is_builtin(char *command);
int		is_valid(char *var);
char	*rem_quotes_export(char *s);
char	*check_expansion(char *str, int *i);
void	update_shell_lvl(void);
void	handle_signals(void);
void	control_d(char *str);
void	sig_handler(int signal);
int		search_expansion(t_cmd *cmds);
t_cmd	*get_head(t_cmd *lst);
void	init_data_var2(void);
void	init_data_var(void);

#endif