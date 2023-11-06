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

void	heredoc_error()
{
	printf("error heredoc\n");
}

 void    child_heredoc(t_cmd *cmd)
{
	char *line;

	signal(SIGQUIT, SIG_IGN); //says signal c/ should be ignored
	signal(SIGINT, handle_signals); //when control c handle
	close(data()->here[0]);
	while (1)
	{
		write(0, "> ", 2);
		line = get_next_line(0);
		if (!line)
		{
			heredoc_error();
			general_free(cmd, 1, 1, 0);
			break;
		}
		if (!ft_strncmp(line, cmd->redir->file, ft_strlen(cmd->redir->file)))
		{
			free(line);
			general_free(cmd, 1, 1, 0);
			break;
		}
		line = expansion_heredoc(line);
		write(data()->here[1], line, ft_strlen(line));
		free(line);
	}
	close(data()->here[1]);
	exit(0);
}

int heredoc(t_cmd *cmd)
{
	int pid;

	print_list(cmd);
	if (pipe(data()->here) == -1)
		perror("");
	pid = fork();
	if (pid == 0)
	{
		while (cmd->redir)
		{
			child_heredoc(cmd);
			cmd->redir = cmd->redir->next;
		}
	}
	close(data()->here[1]);
	wait(&pid);
	if (cmd->redir->next == NULL)
		return (data()->here[0]);
	else
	{
		close(data()->here[0]);
		return (0);
	}
}
