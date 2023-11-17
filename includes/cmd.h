/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 22:20:58 by svalente          #+#    #+#             */
/*   Updated: 2023/11/17 12:42:36 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <string_lib.h>
# include <builtin.h>
# include <stdbool.h>
# include <minishell.h>

typedef struct s_redir
{
	int				fd;
	int				redir;
	char			*file;
	struct s_redir	*next;
	struct s_redir	*prev;
}	t_redir;

typedef struct s_cmd
{
	int				reds;
	struct s_cmd	*prev;
	struct s_cmd	*next;
	char			*path;
	char			**args;
	int				pipe[2];
	t_redir			*redir;
	int				fd_in;
	int				fd_out;
	pid_t			pid;
	bool			error;
}	t_cmd;

typedef struct s_data
{
	t_env			*envp;
	int				here[2];
	char			**del;
	int				in_heredoc;
	int				redir;
	int				exit;
	int				*pipe_here;
	t_cmd			*pointer_cmd;
	bool			error;
}	t_data;

t_data	*data(void);

int		envp(void);
int		pwd(void);
int		echo(t_cmd *cmd);
void	exit_builtin(t_cmd *cmd);
int		cd(t_cmd *cmd);
int		export(t_cmd *cmd);
int		unset(char **cmd);
void	execution(t_cmd *cmd);
void	get_env_to_list(char **env);
void	print_list(t_cmd *lst);
void	cmdlstclear(t_cmd **lst);
int		create_list(t_cmd **lst, char **args);
int		search_expansion(t_cmd *cmds);
char	*expansion(char *str, int *i);
void	general_free(t_cmd *cmd, bool env, bool close, bool exit);
char	*ft_strjoin(char *s1, char *s2);
int		heredoc(t_cmd *cmd);
void	cmd_add_back(t_cmd **lst, t_cmd *new);
t_cmd	*cmd_last_node(t_cmd *lst);
t_cmd	*cmd_new_node(char **args);
void	exitbuiltin(int i);

#endif