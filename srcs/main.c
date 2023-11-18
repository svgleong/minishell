/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:39:21 by svalente          #+#    #+#             */
/*   Updated: 2023/11/18 15:55:27 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_env	*env(void)
{
	static t_env	env;

	return (&env);
}

t_data	*data(void)
{
	static t_data	data;

	return (&data);
}

void	main_loop(char **env)
{
	char	*rl;

	rl_catch_signals = 0;
	signal(SIGQUIT, sig_handler);
	signal(SIGINT, sig_handler);
	env_checker(env);
	init_data_var2();
	while (1)
	{
		init_data_var();
		rl = readline("Painshell: ");
		control_d(rl);
		if (!rl || !rl[0])
			continue ;
		add_history(rl);
		if (!parser(rl))
			continue ;
		print_list(data()->pointer_cmd);
		execution(data()->pointer_cmd);
		cmdlstclear(&data()->pointer_cmd);
	}
	free(rl);
	rl = NULL;
	cmdlstclear(&data()->pointer_cmd);
	rl_clear_history();
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	main_loop(env);
	return (0);
}
