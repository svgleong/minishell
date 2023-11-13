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

int ft_strdigit(char *s)
{
	int i;

	i = -1;
	while (s[++i])
		if (!ft_isdigit(s[i]))
			return (0);
	return (1);
}

void    exit_builtin(t_cmd *cmd)
{
    int	 	status;

	if (!cmd->args || !cmd->args[1])
		exit(data()->exit);
	if (!ft_strdigit(cmd->args[1]) || ft_atol(cmd->args[1]) == 3737373737)
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		status = 2;
	}
	else if (cmd->args[2])
	{
		ft_putstr_fd("exit: too many arguments or outside limits\n", 2);
		status = 1;
	}
	else
	{
		status = ft_atoi(cmd->args[1]);
		status %= 256 + 256 * (status < 0);
	}
	if (!cmd->next)
		ft_putstr_fd("exit\n", 2);
	data()->exit = status;
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