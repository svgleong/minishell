//exit [args]
//if args > 2 -> shows error of misusing builtin
//arg should be an int, if not show error
// exit n where n within 10 digits
// exit finish proccess and gives exit code
// exit code = n & 256

#include <minishell.h>

void    exit_builtin(t_cmd *cmd)
{
    int i;

    i = 0;
    if (!cmd->args[1])
        return ;
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
    // printf("exit code: %d\n", data()->exit);
}
// ls > out | cat < Makefile > out2a