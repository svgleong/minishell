
#include <minishell.h>

void	which_builtin(t_cmd *cmd)
{
	if (!ft_strncmp(cmd->args[0], "env", ft_strlen(cmd->args[0])))
		envp(cmd);
	else if (!ft_strncmp(cmd->args[0], "pwd", ft_strlen(cmd->args[0])))
		pwd();
	else if (!ft_strncmp(cmd->args[0], "echo", ft_strlen(cmd->args[0])))
		echo(cmd);
	else if (!ft_strncmp(cmd->args[0], "cd", ft_strlen(cmd->args[0])))
		cd(cmd);
	else if (!ft_strncmp(cmd->args[0], "export", ft_strlen(cmd->args[0])))
		export(cmd);
	else if (!ft_strncmp(cmd->args[0], "unset", ft_strlen(cmd->args[0])))
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
	char	*path = getenv("PATH");
	char	**matrix;
	char	*executable_path;

	if (path != NULL) {
		matrix = ft_split(path, ':');
		while (matrix != NULL && *matrix != NULL) {
			executable_path = ft_strjoin_free(ft_strjoin_free(*matrix, "/", 0), command, 1);
			if (access(executable_path, X_OK) == 0)
				return (executable_path);
			free(executable_path);
			matrix++;
		}	
	}
	return (command);
}

void	exec(t_cmd *cmd)
{
	if(execve(find_command_path(cmd->args[0]), cmd->args, env_to_matrix()) == -1) 
	{
		ft_putstr_fd("Command not found\n", STDERR_FILENO);
		data()->exit = 127;
		exit(data()->exit);
	}
}

void	exec_builtin(t_cmd *cmd)
{
	which_builtin(cmd);
	//general_free(cmd, 1, 1, 0);
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
	if (data()->exit == 0)
	{
		if (cmd_is_builtin(cmd->args[0]) == 1)
		{
			exec_builtin(cmd);
			exit (EXIT_SUCCESS);
		}
		else
			exec(cmd);
	}
	//general_free(cmd, 1, 1, 0);
	exit(data()->exit);
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
		if (cmd->fd_in != -1)
			close(cmd->fd_in);
		if ( cmd->fd_out != -1)
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
		if (cmd_is_builtin(cmd->args[0]) && !cmd->next && data()->redir == 0)
		{
			which_builtin(cmd);
			cmd = cmd->next;
			continue ;
		}
		if (cmd->args)
			pipe_handler(cmd);
		cmd = cmd->next;
	}
	cmd = head;
	while (cmd)
	{
		waitpid(cmd->pid, &status, 0);
		cmd = cmd->next;
	}
	if (WIFEXITED(status))
		data()->exit = WEXITSTATUS(status);
}
