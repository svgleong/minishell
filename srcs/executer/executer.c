
#include <minishell.h>

void	is_built_in(t_cmd *cmd)
{
	if (!ft_strncmp(cmd->args[0], "env", 3))
		type()->f = env_builtin;
	else if (!ft_strncmp(cmd->args[0], "pwd", 3))
		type()->f = pwd_bi;
}

int	cmd_is(t_cmd *cmd)
{
	if (!ft_strncmp(cmd->args[0], "pwd", 3) || \
		!ft_strncmp(cmd->args[0], "cd", 2) || \
		!ft_strncmp(cmd->args[0], "exit", 4) || \
		!ft_strncmp(cmd->args[0], "env", 3) || \
		!ft_strncmp(cmd->args[0], "export", 6) || \
		!ft_strncmp(cmd->args[0], "unset", 5))
		return (1);
	else
		return (0);
}

char	*find_command_path(char *command)
{
	char	*path = getenv("PATH");
	char	**matrix;
	char	*executable_path;

	if (access(command, X_OK) == 0) {
			printf("success other\n");
		return (command);
	}

	if (path != NULL) {
		matrix = ft_split(path, ':');
		while (matrix != NULL && *matrix != NULL) {
			executable_path = ft_strjoin_free(ft_strjoin_free(*matrix, "/", 0), command, 1);
			if (access(executable_path, X_OK) == 0) {
				printf("PATH: %s\n", executable_path);
				return (executable_path);
			}
			free(executable_path);
			matrix++;
		}
	}
	printf("path not found or doesnt exist");
	return NULL;
}

void	normal_execution(t_cmd *cmd)
{
	printf("\nPATH FOR EXECUTION: %s\n", cmd->path);
	if (execve(cmd->path, cmd->args, env_to_matrix()) == -1)
		printf("error in execution\n");
	else
		printf("success execution\n");

}
void	core_execution(t_cmd *cmd)
{
	if (cmd_is(cmd))
	{
		type()->f(cmd);
		return;
	}
	else
		normal_execution(cmd);
}


void	execution(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->args[0])
			{
				cmd->path = find_command_path(cmd->args[0]);
				is_built_in(cmd);
				core_execution(cmd);
			}
		cmd = cmd->next;
	}
}


 