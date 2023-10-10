
#include <minishell.h>

void	exec(t_cmd *cmd)
{
	if (execve(cmd->path, cmd->args, env_to_matrix()) == -1)
		printf("error execve\n");
}

void	which_builtin(t_cmd *cmd)
{
	if (!ft_strncmp(cmd->args[0], "env", 3))
		type()->f = env_builtin;
	else if (!ft_strncmp(cmd->args[0], "pwd", 3))
		type()->f = pwd_bi;
	else if (!ft_strncmp(cmd->args[0], "echo", 4))
		type()->f = echo_bi;
	else
		type()->f = exec;
	
}

int	cmd_is_builtin(char *command)
{
	if (!ft_strncmp(command, "pwd", 3) || \
		!ft_strncmp(command, "cd", 2) || \
		!ft_strncmp(command, "exit", 4) || \
		!ft_strncmp(command, "env", 3) || \
		!ft_strncmp(command, "export", 6) || \
		!ft_strncmp(command, "unset", 5))
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
	printf("path not found or doesnt exist\n");
	return NULL;
}

/* void	main_execution(t_cmd *cmd)
{
	dup2(cmd->fd_in, STDIN_FILENO);
	if (cmd->next)
		dup2(cmd->pipe[1], STDOUT_FILENO);
	close(cmd->pipe[0]);
	close(cmd->pipe[1]);
	if (execve(find_command_path(cmd->args[0]), cmd->args, env_to_matrix()) == -1) 
	{
		printf("error execve\n");
		exit(0);
	}
} */

void	core_execution(t_cmd *cmd)
{
	int pid;
	if (cmd_is_builtin(cmd->args[0]) == 1 && !cmd->next)
		type()->f(cmd);
	else
	{
		pid = fork();
		if (pipe(cmd->pipe) == -1)
			printf("pipe error\n");
		if (pid == -1)
			printf("fork error\n");
		if (pid == 0)
		{
			if (cmd->prev)
				dup2(cmd->pipe[0], STDIN_FILENO);
			if (cmd->next)
				dup2(cmd->pipe[1], STDOUT_FILENO);
			type()->f(cmd);
			close(0);
			exit(0);
		}
	}
}

void	execution(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->args[0])
		{
			cmd->path = find_command_path(cmd->args[0]);
			which_builtin(cmd);
			core_execution(cmd);
		}
		if (!cmd->next)
			break ;
		cmd = cmd->next;
	}
}


/* void	normal_execution(t_cmd *cmd)
{
	int pid;

	while (cmd)
	{
		if (pipe(cmd->pipe) == -1)
			printf("pipe error\n");
		pid = fork();
		if (pid == -1)
			printf("fork error\n");
		if (pid == 0)
			main_execution(cmd);
		cmd = cmd->next;
	}


} */


/* void	execution(t_cmd *cmd)
{
	int pid;
	
} */

/* void	execution(t_cmd	*cmd)
{
	if (cmd_is_builtin(cmd->args[0]) == 1 && !cmd->next)
	{
		printf("Entrou builtin\n");
		is_built_in(cmd);
	}
	else
		normal_execution(cmd);
} */


 