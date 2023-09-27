/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:39:21 by svalente          #+#    #+#             */
/*   Updated: 2023/09/27 16:52:09 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <parser.h>

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	char *rl;
	t_cmd *lst;
	char **tmp;
	lst = NULL;
	
	while (1)
	{
		rl = readline("Painshell: ");
		add_history(rl);
		if (!checker(rl))
			continue ;
		tmp = separate_args(rl);
		create_list(&lst, tmp);
		redirections(&lst);
		print_list(lst);
		cmdlstclear(&lst);
		//free (tmp);
	}
	free(rl);
	rl = NULL;
	rl_clear_history();
	return (0);
}