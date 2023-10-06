/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:39:21 by svalente          #+#    #+#             */
/*   Updated: 2023/10/06 12:26:02 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <minishell.h>

void	sig_handler(int signal)
{
	if (signal == SIGQUIT)
		return ;
	if (signal == SIGINT )
	{
		// this_env()->status = 130;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	return ;
}


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


/* int main(int ac, char **av, char **env)
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
} */

t_data	*data(void)
{
	static t_data	data;
	
	return (&data);
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	char *rl;
	t_cmd *lst;
	char **tmp;
	lst = NULL;

	get_env_to_list(env);
	//print_env();
	rl_catch_signals = 0;
	signal(SIGQUIT, sig_handler);
	signal(SIGINT, sig_handler);
	while (1)
	{
		rl = readline("Painshell: ");
		if (!rl)
			return 1;
		add_history(rl); // nao pode guardar so espacoes nem empty
		if (!checker(rl))
			continue ;
		tmp = separate_args(rl);
		create_list(&lst, tmp);
		//redirections(&lst);
		print_list(lst);
		cmdlstclear(&lst);
		//free (tmp);
	}
	free(rl);
	rl = NULL;
	
	rl_clear_history();
	return (0);
}