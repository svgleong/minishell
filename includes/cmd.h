/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parallels <parallels@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 22:20:58 by svalente          #+#    #+#             */
/*   Updated: 2023/10/12 15:48:22 by parallels        ###   ########.fr       */
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

/* 	">" -> 0
	"<" -> 1
	">>" -> 2
	"<<" -> 3 */



typedef struct s_cmd
{
	struct s_cmd	*prev;
	struct s_cmd	*next;
	char			*path;
	char			**args;
	int				pipe[2];
	int				fd_in;
	int				fd_out;
	int				redir;
	pid_t				pid;
}	t_cmd;

typedef struct s_type
{
	void	(*f)(t_cmd *cmd);
}	t_type;

t_type	*type(void);	
void    env_builtin(t_cmd *cmd);
void    pwd_bi(t_cmd *cmd);
void    echo_bi(t_cmd *cmd);

void	create_list(t_cmd **lst, char **args);
void	print_list(t_cmd *lst);
void	cmdlstclear(t_cmd **lst);

// Expansion resources
int		search_expansion(t_cmd *cmds);
char	*expansion(char *str, int i);

#endif