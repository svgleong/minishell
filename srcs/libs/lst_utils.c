#include <minishell.h>

void	which_builtin(t_cmd *cmd)
{
	if (!ft_strcmp(cmd->args[0], "env"))
		envp(cmd);
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
	else
		ft_putstr_fd("Command not found\n", STDERR_FILENO);
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

	path = getenv("PATH");
	if (path != NULL)
	{
		matrix = ft_split(path, ':');
		while (matrix != NULL && *matrix != NULL)
		{
			executable_path = ft_strjoin_free(ft_strjoin_free(*matrix, "/", 0),
					command, 1);
			if (access(executable_path, X_OK) == 0)
				return (executable_path);
			free(executable_path);
			matrix++;
		}
	}
	return (command);
}

char	**env_to_matrix()
{
	int		len;
	char	**matrix;
	t_env	*temp;

	len = 0;
	temp = (t_env *)data()->envp;
	while (temp)
	{
		len++;
		temp = temp->next;
	}
	matrix = malloc(sizeof(char *) * (len + 1));
	if (!matrix)
		return (NULL);
	temp = (t_env *)data()->envp;
	len = 0;
	while (temp)
	{
		matrix[len] = ft_strdup(temp->content);
		if (!matrix[len])
			return (NULL);
		temp = temp->next;
		len++;
	}
	matrix[len] = NULL;
	return (matrix);
}