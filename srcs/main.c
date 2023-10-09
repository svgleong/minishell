/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzarichn <mzarichn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:39:21 by svalente          #+#    #+#             */
/*   Updated: 2023/10/09 16:34:57 by mzarichn         ###   ########.fr       */
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

t_data	*data(void)
{
	static t_data	data;
	return (&data);
}

t_type	*type(void)
{
	static t_type	type;
	return (&type);
}

void	print_args(t_cmd *cmd)
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
	t_cmd cmd = {
		.args = (char *[]){"export", NULL}
	};
	print_args(&cmd);
	get_env_to_list(env);
	execution(&cmd);
	//printf("%i: list size\n", list_size());
	//can_execute_command(cmd.args[0]);
	//pwd_bi();
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
		if (rl == NULL || !ft_strncmp(rl, "exit", 5))
		{
			free(rl);	
			exit(0);
		}
		add_history(rl);
		if (!checker(rl))
			continue ;
		tmp = separate_args(rl);
		create_list(&lst, tmp);
		//redirections(&lst);
		//print_list(lst);
		cmdlstclear(&lst);
		//free (tmp);
	}
	free(rl);
	rl = NULL;
	
	rl_clear_history();
	return (0);
} */