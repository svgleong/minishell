/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:41:17 by svalente          #+#    #+#             */
/*   Updated: 2023/11/18 15:41:48 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exitbuiltin(int i)
{
	int	pid;

	pid = fork();
	if (!pid)
	{
		general_free(data()->pointer_cmd, 1, 1, 0);
		exit(i);
	}
	return ;
}

int	ft_strdigit(char *s)
{
	int	i;

	i = -1;
	if (s[0] == '-' || s[0] == '+')
		i++;
	while (s[++i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
	}
	return (1);
}

int	status_calc(char *arg)
{
	int	status;

	status = 0;
	status = ft_atoi(arg);
	status %= 256 + 256 * (status < 0);
	return (status);
}

int	not_numeric(t_cmd *cmd)
{
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(cmd->args[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	return (2);
}

int	exit_builtin(t_cmd *cmd)
{
	int	status;

	status = 0;
	if (!cmd->next)
		ft_putstr_fd("exit\n", 2);
	if (!cmd->args || !cmd->args[1])
		general_free(cmd, 1, 0, 1);
	if (!ft_strdigit(cmd->args[1]) || ft_atol(cmd->args[1]) == 3737373737)
		status = not_numeric(cmd);
	else if (cmd->args[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		if (data()->exit == 0)
			return (1);
		return (data()->exit);
	}
	else
		status = status_calc(cmd->args[1]);
	if (cmd->prev)
		return (status);
	data()->exit = status;
	general_free(cmd, 1, 1, 1);
	return (status);
}
