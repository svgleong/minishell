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
	// if (signal == SIGQUIT)
	// 	SIG_IGN ;
	if (signal == SIGINT)
	{
		write(2, "\n ", 1);
		general_free(data()->pointer_cmd, 1, 1, 0);
		close(data()->here[0]);
		close(data()->here[1]);
		exit(1);
	}
	/* (void)signal;
	general_free(data()->pointer_cmd, 1, 1, 0);
	close(data()->here[0]);
	close(data()->here[1]);
	exit(EXIT_FAILURE); */
}

int	check_quotes_here(char *s)
{
	int i = -1;
	int	j = 0;
	int	flag = 0;

	while (s[++i] && flag == 0)
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			j = i + 1;
			while (s[j])
			{
				if (s[j] == '\'' || s[j] == '\"')
				{
					flag = 1;
					break;
				}
				j++;
			}
		}
	}
	if (flag == 1)
		return (1);
	return (0);
}

void remove_quotes_here(char *str) {
    int len;
    int i;
	int j;

	i = 0;
	j = 0;
	len = strlen(str);
    while (i < len) {
        if ((str[i] == '\'' && str[i + 1] == '\"') || (str[i] == '\"' && str[i + 1] == '\''))
            i += 2; // Skip the pair of quotes
        else if (str[i] == '\'' || str[i] == '\"')
            i++; // Skip the single quote or double quote
        str[j++] = str[i++];
    }
    str[j] = '\0';
}

 void    child_heredoc(t_cmd *cmd)
{
	char *line;
	bool	quote = false;

	while (check_quotes_here(cmd->redir->file) == 1)
	{
		remove_quotes_here(cmd->redir->file);
		quote = true;
	}
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
		if (quote == false)
			line = expansion_heredoc(line);
		if (line[ft_strlen(line)] == '\0')
			line[ft_strlen(line)] = '\n';
		write(data()->here[1], line, ft_strlen(line));
		free(line);
	}
	close(data()->here[1]);
	exit(0);
}

int heredoc(t_cmd *cmd)
{
	int pid;
  int status;

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
	waitpid(pid, &status, 0);
  if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
  {
    close(data()->here[0]);
    return (-1);
  }
	return (data()->here[0]);
}
