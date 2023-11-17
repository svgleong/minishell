/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:41:17 by svalente          #+#    #+#             */
/*   Updated: 2023/11/17 19:54:55 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#include <sys/stat.h>

void	error_before_execute(char *path, char **matrix)
{
	struct stat	st;

	//printf("entrei error before\n");
	
	if (stat(path, &st) == -1)
		return ;
	if (S_ISDIR(st.st_mode) && path && (!ft_strncmp("./", path, 2) || path[0] == '/'))
	{
		exec_error("", " Is a directory", 126);
		free(path);
		free_matrix(matrix);
		general_free(data()->pointer_cmd, 1, 1, 1);
	}
}

void	exec(t_cmd *cmd)
{
	char	**matrix;
	char	*path;

	matrix = env_to_matrix();
	path = find_command_path(cmd->args[0]);
	
	//fprintf(stderr, "[%s]", path);
	//error_before_execute(path, matrix);
	if (execve(path, cmd->args, matrix) == -1)
	{
		fprintf(stderr, "arg[0] %s\n", cmd->args[0]);
		if (errno == 13)
		{
			fprintf(stderr, "entrei 13\n");
			// perror("Error");
			// data()->exit = 126;
			// free(path);
			// general_free(NULL, 1, 1, 1);
			perror("Error");
			data()->exit = 126;
			free(path);
			free_matrix(matrix);
			general_free(cmd, 1, 1, 1);
		}
		else
		{
			exec_error(cmd->args[0], ": command not found\n", 127);
			general_free(NULL, 1, 1, 1);
		}
		free_matrix(matrix);
		general_free(cmd, 1, 1, 1);
	}
}

void	core_execution(t_cmd *cmd)
{
	print_list(data()->pointer_cmd);
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
	if (cmd_is_builtin(cmd->args[0]) == 1 && cmd->error == false)
	{
		data()->exit = which_builtin(cmd);
		general_free(cmd, 1, 1, 1);
	}
	else if (cmd->error == false)
		exec(cmd);
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
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
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

void	execution_loop(t_cmd *cmd)
{
	while (cmd)
	{
		if (!cmd->args[0])
		{
			if (cmd->next)
			{
				heredoc_exception(cmd);
				cmd = cmd->next;
				continue ;
			}
			break ;
		}
		if (cmd_is_builtin(cmd->args[0]) && !cmd->next && data()->redir == 0 && cmd->error == false)
		{
			data()->exit = which_builtin(cmd);
			exitbuiltin(data()->exit);
			cmd = cmd->next;
			continue ;
		}
		if (cmd->args && cmd->error == false)
			pipe_handler(cmd);
		cmd = cmd->next;
	}
}

void	execution(t_cmd *cmd)
{
	int		status;

	status = 0;
	execution_loop(cmd);
	cmd = data()->pointer_cmd;
	while (cmd)
	{
		waitpid(cmd->pid, &status, 0);
		cmd = cmd->next;
	}
	if (WIFEXITED(status))
		data()->exit = WEXITSTATUS(status);
}
