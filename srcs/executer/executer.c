
#include <minishell.h>

void	exec(t_cmd *cmd)
{
	if (execve(cmd->path, cmd->args, env_to_matrix()) == -1)
		printf("error execve\n");
}

void	execute_builtin(t_cmd *cmd)
{
	if (!ft_strncmp(cmd->args[0], "env", 3))
		type()->f = env_builtin;
	else if (!ft_strncmp(cmd->args[0], "pwd", 3))
		type()->f = pwd_bi;
	else if (!ft_strncmp(cmd->args[0], "echo", 4))
		type()->f = echo_bi;
	else if (!ft_strncmp(cmd->args[0], "cd", 2))
		type()->f = cd_bi;
	else if (!ft_strncmp(cmd->args[0], "export", 6))
		type()->f = export_bi;
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
		!ft_strncmp(command, "unset", 5) || \
		!ft_strncmp(command, "echo", 4))
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
		return (command);
	}

	if (path != NULL) {
		matrix = ft_split(path, ':');
		while (matrix != NULL && *matrix != NULL) {
			executable_path = ft_strjoin_free(ft_strjoin_free(*matrix, "/", 0), command, 1);
			if (access(executable_path, X_OK) == 0) {
				// printf("PATH: %s\n", executable_path);
				return (executable_path);
			}
			free(executable_path);
			matrix++;
		}
	}
	printf("path not found or doesnt exist\n");
	return NULL;
}

void core_execution(t_cmd *cmd)
{
	if (cmd->fd_in != -1)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	close(cmd->pipe[0]);
	if (cmd->fd_out != -1)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
	else if (cmd->next)
		dup2(cmd->pipe[1], STDOUT_FILENO);
	close(cmd->pipe[1]);
	execve(find_command_path(cmd->args[0]), cmd->args, env_to_matrix());
	exit(0);
}
void	pipe_handler(t_cmd *cmd)
{
	if (pipe(cmd->pipe) == -1)
		printf("pipe error\n");
	cmd->pid = fork();
	if (cmd->pid == -1)
		printf("fork error\n");
	if (cmd->pid == 0)
		core_execution(cmd);
	else
	{
		if (cmd->next)
			cmd->next->fd_in = dup(cmd->pipe[0]);
		if (cmd->fd_in != 0) //caso cat cat cat
			close(cmd->fd_in);
		if ( cmd->fd_out != 1)
			close(cmd->fd_out);
		close(cmd->pipe[0]);
		close(cmd->pipe[1]);
	}	
}


void	execution(t_cmd *cmd)
{
	t_cmd *head = cmd;
	int status;
	while (cmd)
	{
		if (cmd_is_builtin(cmd->args[0]) == 1 && !cmd->next)
		{
			execute_builtin(cmd);
		}
		else if (cmd->args)
		{
			//cmd->path = find_command_path(cmd->args[0]);
			pipe_handler(cmd);
		}
		if (!cmd->next)
			break ;
		cmd = cmd->next;
	}
	cmd = head;
	while (cmd)
	{
		waitpid(cmd->pid, &status, 0);
		if (!cmd->next)
			break ;
		cmd = cmd->next;
	}
}
