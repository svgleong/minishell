/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzarichn <mzarichn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:39:21 by svalente          #+#    #+#             */
/*   Updated: 2023/09/27 16:32:11 by mzarichn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
# include <readline/readline.h>
# include <readline/history.h> 
# include <stdio.h>


#include <executer.h>

t_env	*env(void)
{
	static t_env env;
	return (&env);
}

t_export_env	*export_env(void)
{
	static t_export_env export_env;
	return (&export_env);
}

void	print_args(t_cmdd *cmd)
{
	printf("Debug Args: ");
    for (int i = 0; cmd->args[i] != NULL; i++) {
        printf("%s ", cmd->args[i]);
    }
	printf("\n");
}


int main(int ac, char **av, char **env)
{
    (void)ac;
	(void)av;
	t_cmdd cmd = {
		.args = (char *[]){"echo", "-nnnnnnnni", "ola", NULL}
	};
	print_args(&cmd);
	//pwd_bi();

	
	t_env *env_list;
    env_list = NULL;
	env_bi(env, env_list);
	//list_bubble_sort(env);


	return (0);
}

/* int main(int ac, char **av, char **env)
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
} */