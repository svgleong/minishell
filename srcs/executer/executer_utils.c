/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:41:17 by svalente          #+#    #+#             */
/*   Updated: 2023/11/17 12:49:12 by svalente         ###   ########.fr       */
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

int	check_access(char *executable_path, char **matrix)
{
	if (access(executable_path, X_OK) == 0)
	{
		free_matrix(matrix);
		return (0);
	}
	return (1);
}

char	*find_command_path(char *command)
{
	char	*path;
	char	**matrix;
	char	*executable_path;
	char	*temp;
	int		i;

	path = node_value(search_env("PATH"));
	i = -1;
	if (path != NULL)
	{
		matrix = ft_split(path, ':');
		free(path);
		while (matrix != NULL && matrix[++i] != NULL)
		{
			temp = ft_strjoin_free(matrix[i], "/", 0);
			executable_path = ft_strjoin_free(temp, command, 1);
			if (!check_access(executable_path, matrix))
				return (executable_path);
			free(executable_path);
		}
		free_matrix(matrix);
	}
	return (command);
}
