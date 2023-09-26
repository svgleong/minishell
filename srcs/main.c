/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:39:21 by svalente          #+#    #+#             */
/*   Updated: 2023/09/26 12:51:00 by svalente         ###   ########.fr       */
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
		tmp = separate_args(rl);
		// printf("tmp[0] = %s\n", tmp[0]);
		create_list(&lst, tmp);
		print_list(lst);
		//check_quotes(rl);
		//create_list(rl, &lst);
		cmdlstclear(&lst);
		free (tmp);
	}
	free(rl);
	rl = NULL;
	return (0);
}