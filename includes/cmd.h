/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parallels <parallels@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 22:20:58 by svalente          #+#    #+#             */
/*   Updated: 2023/10/17 21:33:08 by parallels        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <string.h>
#include <builtin.h>
#include <stdbool.h>

/* 	">" -> 3
	"<" -> 4
	">>" -> 1
	"<<" -> 2 */

typedef struct s_redir
{
	int				fd;
	int				redir;
	char			*file;
	struct s_redir	*next;
}	t_redir;



typedef struct s_cmd
{
	struct s_cmd	*prev;
	struct s_cmd	*next;
	char			*path;
	char			**args;
	int				pipe[2];
	t_redir			*redir;
	int				fd_in;
	int				fd_out;
	pid_t			pid;
}	t_cmd;

	
void    envp();
void    pwd();
void    echo(t_cmd *cmd);
void    exit_builtin(t_cmd *cmd);
void 	cd(t_cmd *cmd);
void	export(t_cmd *cmd);
void    unset(char **cmd);
void	execution(t_cmd *cmd);
void	get_env_to_list(char **env);

void	create_list(t_cmd **lst, char **args);
void	print_list(t_cmd *lst);
void	cmdlstclear(t_cmd **lst);

// Expansion resources
int		search_expansion(t_cmd *cmds);
char	*expansion(char *str, int i);

//frees
void	general_free(t_cmd *cmd, bool env, bool close, bool exit);
void    free_env_list(t_env **lst);


char    *ft_strjoin(char *s1, char *s2);
int    heredoc(t_cmd *cmd);

#endif