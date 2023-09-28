/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzarichn <mzarichn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 22:20:58 by svalente          #+#    #+#             */
/*   Updated: 2023/09/28 11:48:40 by mzarichn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <string.h>

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
}	t_cmd;

void	create_list(char *rl, t_cmd **lst);
void	print_list(t_cmd *lst);
void	cmdlstclear(t_cmd **lst);

#endif