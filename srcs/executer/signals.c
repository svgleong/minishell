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
	if (signal == SIGINT && !data()->pointer_cmd)
	{
		data()->exit = 130;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
		write(1, "\n", 1);
	// else if (signal == SIGINT)
	// {
	// 	write(1, "\n", 1);
	// 	rl_on_new_line();
	// 	rl_replace_line("", 0);
	// 	rl_redisplay();
	// }
	return ;
}
