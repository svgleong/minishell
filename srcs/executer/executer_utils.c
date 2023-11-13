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

void	which_builtin(t_cmd *cmd)
{
	if (!ft_strcmp(cmd->args[0], "env"))
		envp();
	else if (!ft_strcmp(cmd->args[0], "pwd"))
		pwd();
	else if (!ft_strcmp(cmd->args[0], "echo"))
		echo(cmd);
	else if (!ft_strcmp(cmd->args[0], "cd"))
		cd(cmd);
	else if (!ft_strcmp(cmd->args[0], "export"))
		export(cmd);
	else if (!ft_strcmp(cmd->args[0], "unset"))
		unset(cmd->args);
	else if (!ft_strcmp(cmd->args[0], "exit"))
		exit_builtin(cmd);
	else
		ft_putstr_fd("command not found\n", STDERR_FILENO);
}

int	cmd_is_builtin(char *command)
{
	if (!ft_strcmp(command, "pwd") || \
		!ft_strcmp(command, "cd") || \
		!ft_strcmp(command, "exit") || \
		!ft_strcmp(command, "env") || \
		!ft_strcmp(command, "export") || \
		!ft_strcmp(command, "unset") || \
		!ft_strcmp(command, "echo"))
		return (1);
	else
		return (0);
}

char	*find_command_path(char *command)
{
	char	*path;
	char	**matrix;
	char	*executable_path;
	char	*temp;
	int		i;

	path = node_value(search_env("PATH"));
	i = 0;
	if (path != NULL)
	{
		matrix = ft_split(path, ':');
		free(path);
		while (matrix != NULL && matrix[i] != NULL)
		{
			temp = ft_strjoin_free(matrix[i], "/", 0);
			executable_path = ft_strjoin_free(temp, command, 1);
			if (access(executable_path, X_OK) == 0)
				return (executable_path);
			free(executable_path);
			i++;
		}
		free_matrix(matrix);
	}
	return (command);
}
