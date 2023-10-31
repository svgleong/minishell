/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:39:21 by svalente          #+#    #+#             */
/*   Updated: 2023/10/19 09:58:46 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <minishell.h>

void	control_d(char *str, t_cmd **cmd)
{
	// unsigned char	status;
	(void)cmd;
	if (str)
		return ;
	rl_clear_history();
	write(1, "exit\n", 6);
	if (data()->envp)
		free_env_list(&data()->envp);
	//general_free((*cmd), 1, 1, 1);
	
	// free_memory(this());
	// status = (unsigned char)(data()->envp)->status;
	exit(0);
}

void	sig_handler(int signal)
{
	/* printf("Signal: %d\n", signal);
	printf("sigquit: %d\n", SIGQUIT);
	printf("SIGINT: %d\n", SIGINT);
 */
	if (signal == SIGQUIT)
		return ;
	if (signal == SIGINT )
	{
		data()->exit = 130;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	return ;
}

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
	t_cmd *lst;
	char **tmp;
	lst = NULL;
	if (env)
		get_env_to_list(env);
	rl_catch_signals = 0;
	signal(SIGQUIT, sig_handler);
	signal(SIGINT, sig_handler);
	while (1)
	{
		rl = readline("Painshell: ");
		control_d(rl, &lst);
		if (!rl || !rl[0])
			continue ;
		if (rl == NULL) //|| !ft_strncmp(rl, "exit", 5)
			break ;
		add_history(rl);
		if (!checker(rl))
			continue ;
		tmp = separate_args(rl);
		create_list(&lst, tmp);
		data()->exit = 0;
		execution(lst);
		printf("exit code %d\n", data()->exit);
		cmdlstclear(&lst);
	}
	free(rl);
	rl = NULL;
	cmdlstclear(&lst);
	rl_clear_history();
	return (0);
}
