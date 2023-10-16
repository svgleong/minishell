/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parallels <parallels@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:39:21 by svalente          #+#    #+#             */
/*   Updated: 2023/10/16 16:54:13 by parallels        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <minishell.h>


void	control_d(char *str)
{
	// unsigned char	status;

	if (str)
		return ;
	rl_clear_history();
	write(1, "exit\n", 6);
	// if (this_env()->env)
	// 	alloc().free_matrix((void **)this_env()->env);
	// free_memory(this());
	// status = (unsigned char)(data()->envp)->status;
	exit(0);
}

void	sig_handler(int signal)
{
	printf("Signal: %d\n", signal);
	printf("sigquit: %d\n", SIGQUIT);
	printf("SIGINT: %d\n", SIGINT);

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

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char *rl;
	t_cmd *lst;
	char **tmp;
	lst = NULL;

	get_env_to_list(env);
	rl_catch_signals = 0;
	signal(SIGQUIT, sig_handler);
	signal(SIGINT, sig_handler);
	while (1)
	{
		rl = readline("Painshell: ");
		control_d(rl);
		if (!rl || !rl[0])
			continue ;
		if (rl == NULL || !ft_strncmp(rl, "exit", 5))
		{
			break ;
			free(rl);
			free_env_list(&data()->envp);
			exit(0);
		}
		add_history(rl);
		if (!checker(rl))
			continue ;
		tmp = separate_args(rl);
		create_list(&lst, tmp);
		//redirections(&lst);
		print_list(lst);
		execution(lst);
		
		cmdlstclear(&lst);
		//free (tmp);
		
	}
	free(rl);
	rl = NULL;
	cmdlstclear(&lst);
	free_env_list(&data()->envp);
	print_env();
	//rl_clear_history();
	return (0);
}
