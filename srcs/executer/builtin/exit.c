//exit [args]
//if args > 2 -> shows error of misusing builtin
//arg should be an int, if not show error
// exit n where n within 10 digits
// exit finish proccess and gives exit code
// exit code = n & 256

#include <minishell.h>

void exitbuiltin(int i)
{
	int pid = fork();
	if (!pid){
		general_free(data()->pointer_cmd, 1, 1, 0);
		exit (i);
	}
	return ;
}

void    exit_builtin(t_cmd *cmd)
{
    int	 	status;
	if (!cmd->next)
		ft_putstr_fd("exit\n", 2);
	if (!cmd->args || !cmd->args[1])
	{
		data()->exit = 0;
		return ;
	}
	status = ft_atoi(cmd->args[1]);
	if (status == -1)
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		data()->exit = 255;
	}
	else if (cmd->args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		data()->exit = 1;
	}
	status %= 256 + 256 * (status < 0);
	data()->exit = status;
	printf("exit status: %d\n", status);
	exit(status);
}

/* void    exit_builtin(t_cmd *cmd)
{
    int i;

    i = 0;
    if (!cmd->args[1])
        general_free(cmd, 1, 1, 1) ;
    ft_putstr_fd("exit\n", 1);
    if (cmd->args[2])
    {
        ft_putstr_fd(" too many arguments\n", 2);
        data()->exit = 1;
        return ;
    }
    while (cmd->args[1][i])
    {
        if (i == 0 && (cmd->args[1][i] == '-' || cmd->args[1][i] == '+'))
            i++;
        if (ft_isdigit(cmd->args[1][i]) == 0)
        {
            ft_putstr_fd(" numeric argument required\n", 2);
            data()->exit = 2;
            break ;
        }
		else if (cmd->args[1][i + 1] == '\0')
			data()->exit = ft_atoi(cmd->args[1]);
        i++;
    }
    general_free(cmd, 1, 1, 1);
    // printf("exit code: %d\n", data()->exit);
} */
// ls > out | cat < Makefile > out2a