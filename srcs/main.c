/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:39:21 by svalente          #+#    #+#             */
/*   Updated: 2023/11/08 12:51:12 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <minishell.h>

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



int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char *rl;
	//char **tmp;
	
	env_checker(env);
	data()->pointer_cmd = NULL;
	rl_catch_signals = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler);
	while (1)
	{
		rl = readline("Painshell: ");
		control_d(rl);
		if (!rl || !rl[0])
			continue ;
		if (rl == NULL)
			break ;
		add_history(rl);
		if (!parser(rl))
			continue ;
		/* if (!checker(rl))
			continue ;
		tmp = separate_args(rl);
		if (!create_list(&data()->pointer_cmd, tmp))
		{
			cmdlstclear(&data()->pointer_cmd);
			continue;
		} */
		data()->exit = 0;
		execution(data()->pointer_cmd);
		cmdlstclear(&data()->pointer_cmd);
	}
	free(rl);
	rl = NULL;
	cmdlstclear(&data()->pointer_cmd);
	rl_clear_history();
	return (0);
}
