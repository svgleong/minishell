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
      {
        free(tmp);
				continue ;
      }
      free(s);
			s = tmp;
			j = -1;
		}
	}
	return (s);
}



void	heredoc_error(char *del)
{
	printf("\nWarning: heredoc delimited by EOF (wanted: \"%s\")\n", del);
}

void	handle_c(int signal)
{
	/* if (signal == SIGQUIT)
		SIG_IGN ;
	else if (signal == SIGINT)
	{
		write(2, " ", 1);
		general_free(data()->pointer_cmd, 1, 1, 0);
		close(data()->here[0]);
		close(data()->here[1]);
		exit(1);
	} */
	(void)signal;
	general_free(data()->pointer_cmd, 1, 1, 0);
	close(data()->here[0]);
	close(data()->here[1]);
	exit(EXIT_FAILURE);
}

 void    child_heredoc(t_cmd *cmd)
{
	char *line;

	close(data()->here[0]);
	while (1)
	{
		write(0, "> ", 2);
		line = get_next_line(0);
		// line = readline("> ");
		if (!line)
		{
			heredoc_error(cmd->redir->file);
			general_free(cmd, 1, 1, 0);
			break;
		}
    if (line[ft_strlen(line) - 1] == '\n')
      line[ft_strlen(line) - 1] = '\0';
		if (!ft_strncmp(line, cmd->redir->file, ft_strlen(line) + 1))
		{
			free(line);
			general_free(data()->pointer_cmd, 1, 1, 0);
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

	if (pipe(data()->here) == -1)
		perror("");
	pid = fork();
	if (pid == 0)
	{
    signal(SIGQUIT, SIG_IGN); //says signal c/ should be ignored
    signal(SIGINT, handle_c); //when control c handle	child_heredoc(cmd);
		child_heredoc(cmd);
	}
	close(data()->here[1]);
	waitpid(pid, NULL, 0);
	return (data()->here[0]);

	/* if (cmd->redir->next == NULL)
	{
		printf("GOOD\n");
		return (data()->here[0]);
	}
	else
	{
		close(data()->here[0]);
		printf("DEBUG\n");
		return (0);
	} */
}
