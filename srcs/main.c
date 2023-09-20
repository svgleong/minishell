/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:39:21 by svalente          #+#    #+#             */
/*   Updated: 2023/09/20 12:43:43 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	char *rl;
	t_cmd *lst;
	
	lst = NULL;
	while (1)
	{
		rl = readline("Painshell: ");
		//printf("%s\n", rl);
		create_list(rl, &lst);
		print_list(lst);
		cmdlstclear(&lst);
		free(rl);
	}
	free(rl);
	rl = NULL;
	return (0);
}