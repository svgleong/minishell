/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzarichn <mzarichn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 22:20:58 by svalente          #+#    #+#             */
/*   Updated: 2023/09/27 15:57:32 by mzarichn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_cmd
{
	struct s_cmd	*prev;
	struct s_cmd	*next;
	char			*cmd;
	char			*path;
	char			**args;
}	t_cmd;

void	create_list(char *rl, t_cmd **lst);
void	print_list(t_cmd *lst);
void	cmdlstclear(t_cmd **lst);

#endif