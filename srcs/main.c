/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:39:21 by svalente          #+#    #+#             */
/*   Updated: 2023/09/25 17:02:38 by svalente         ###   ########.fr       */
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
	char *tmp;
	char **tmp2;
	t_cmd *lst;
			int i = -1;
	lst = NULL;
	while (1)
	{
		rl = readline("Painshell: ");
		add_history(rl);

		i = -1;
		//printf("%s\n", rl);
		tmp = modify_str(rl);
		//printf("str: %s\n", tmp);
		tmp2 = ft_split(tmp, '\2');
		while (tmp2 && tmp2[++i])
			printf("str[%i]: %s\n", i, tmp2[i]);
		tmp2 = free_matrix(tmp2);
		
		//check_quotes(rl);
		//create_list(rl, &lst);
		//print_list(lst);
		//cmdlstclear(&lst);
		free(rl);
		//free (tmp);
	}
	free(rl);
	rl = NULL;
	return (0);
}