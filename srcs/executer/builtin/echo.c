/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:41:17 by svalente          #+#    #+#             */
/*   Updated: 2023/11/13 21:06:17 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	flags(char **cmd, bool *flag)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[++i])
	{
		if (cmd[i][0] != '-')
			return (i);
		if (cmd[i][1] == '\0')
			return (i);
		j = 1;
		while (cmd[i][j])
		{
			if (cmd[i][j] != 'n')
				return (i);
			j++;
		}
		*flag = true;
	}
	return (i);
}

void	echo(t_cmd *cmd)
{
	bool	flag;
	int		i;

	flag = false;
	if (!cmd->args[1])
	{
		printf("\n");
		exitbuiltin(EXIT_SUCCESS);
		return ;
	}
	i = flags(cmd->args, &flag) - 1;
	while (cmd->args[++i])
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
	}
	if (!flag)
		printf("\n");
	exitbuiltin(EXIT_SUCCESS);
}
