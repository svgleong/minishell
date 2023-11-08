#include <minishell.h>

void	exec(t_cmd *cmd)
{
	char	**matrix;

	matrix = env_to_matrix();
	if (execve(find_command_path(cmd->args[0]), cmd->args, matrix) == -1)
	{
		ft_putstr_fd("command not found\n", 2);
		free_matrix(matrix);
		data()->exit = 127;
		// perror("error");
		// data()->exit = errno;
		// fprintf(stderr, "error number: %d\n", data()->exit);
		general_free(cmd, 1, 1, 1);
	}
}

void	core_execution(t_cmd *cmd)
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
			which_builtin(cmd);
			general_free(cmd, 1, 1, 1);
		}
		else
			exec(cmd);
	}
	//print_list(cmd);
}

void	pipe_handler(t_cmd *cmd)
{
	if (pipe(cmd->pipe) == -1)
		printf("pipe error\n");
	cmd->pid = fork();
	if (cmd->pid == -1)
		printf("fork error\n");
	if (cmd->pid == 0)
	{
		core_execution(cmd);
		general_free(cmd, 1, 1, 1);
	}
	if (cmd->next && cmd->next->fd_in == -1)
		cmd->next->fd_in = dup(cmd->pipe[0]);
	if (cmd->fd_in != -1)
		close(cmd->fd_in);
	if (cmd->fd_out != -1)
		close(cmd->fd_out);
	close(cmd->pipe[0]);
	close(cmd->pipe[1]);
}

void	execution(t_cmd *cmd)
{
	t_cmd	*head;
	int		status;

	status = 0;
	head = cmd;
	//print_list(cmd);
	while (cmd)
	{	
		//
		if (!cmd->args[0])
			break ;
		//
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
