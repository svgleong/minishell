/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:41:17 by svalente          #+#    #+#             */
/*   Updated: 2023/11/13 12:31:08 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void handle_signals(void)
{
    signal(SIGINT, sig_handler);
    signal(SIGQUIT, sig_handler);
}
void	control_d(char *str)
{
	//unsigned char	status;
	
	if (str)
		return ;
	rl_clear_history();
	write(1, "exit\n", 6);
	general_free((data()->pointer_cmd), 1, 1, 0);
	//status = (unsigned char)(data()->envp)exit;
	exit(0);
}

void	sig_handler(int signal)
{
	pid_t	pid;
	int		status;

	if (signal == SIGINT && !data()->pointer_cmd)
	{
		data()->exit = 130;
		write(2, "^C\n", 3);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signal == SIGQUIT)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == -1)
			SIG_IGN ;
		else if (data()->in_heredoc == 0)
		{
			write(1, "Quit (core dumped)\n", 20);
			return ;
		}
	}
	return ;
}
