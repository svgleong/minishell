#include <minishell.h>

int	check_dolla(char *s)
{
	int i = -1;
	while (s[++i])
		if (s[i] == '$')
			return (i);
	return (-1);
}
char	*expansion_heredoc(char *s)
{
	int		j;
	char	*tmp;

	j = -1;
	while (s[++j])
	{
		if (s[j] && s[j] == '$')
		{
			tmp = check_expansion(s, j);
			if (tmp[0] == '\2')
				continue ;
			s = tmp;
			j = -1;
		}
	}
	return (s);
}

void    child_heredoc(t_cmd *cmd, int fds[2])
{
	char *line;

	signal(SIGQUIT, SIG_IGN); //says signal c/ should be ignored
	signal(SIGINT, handle_signals); //when control c handle
	while (1)
	{
		write(0, "> ", 2);
		line = get_next_line(0);
		if (!line || !ft_strncmp(line, cmd->redir->file, ft_strlen(cmd->redir->file)))
		{
			free(line);
			free_env_list(&data()->envp);
			cmdlstclear(&cmd);
			break;
		}
		line = expansion_heredoc(line);
		write(fds[1], line, ft_strlen(line));
		free(line);
	}
	close(fds[0]);
	close(fds[1]);
	exit(0);
}

int heredoc(t_cmd *cmd)
{
	int fds[2];
	int pid;

	if (pipe(fds) == -1)
		perror("");
	pid = fork();
	if (pid == 0)
		child_heredoc(cmd, fds);
	close(fds[1]);
	wait(&pid);
	return (fds[0]);
}
