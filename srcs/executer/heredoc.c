/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:41:17 by svalente          #+#    #+#             */
/*   Updated: 2023/11/13 12:31:08 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

void	main_loop_heredoc(t_cmd *cmd, bool quote, char *line)
{
	while (1)
	{
		write(0, "> ", 2);
		line = get_next_line(0);
		if (!line)
		{
			heredoc_error(cmd->redir->file);
			general_free(cmd, 1, 1, 0);
			break ;
		}
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (!ft_strncmp(line, cmd->redir->file, ft_strlen(line) + 1))
		{
			free(line);
			general_free(data()->pointer_cmd, 1, 1, 0);
			break ;
		}
		if (quote == false)
			line = expansion_heredoc(line);
		if (line[ft_strlen(line)] == '\0')
			line[ft_strlen(line)] = '\n';
		write(data()->here[1], line, ft_strlen(line));
		free(line);
	}
}

void	child_heredoc(t_cmd *cmd)
{
	bool	quote;
	char	*line;

	quote = false;
	line = NULL;
	while (check_quotes_here(cmd->redir->file) == 1)
	{
		remove_quotes_here(cmd->redir->file);
		quote = true;
	}
	close(data()->here[0]);
	main_loop_heredoc(cmd, quote, line);
	close(data()->here[1]);
	exit(0);
}

int	heredoc(t_cmd *cmd)
{
	int	pid;
	int	status;

	data()->in_heredoc = 1;
	status = 0;
	if (pipe(data()->here) == -1)
		perror("");
	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handle_c);
		child_heredoc(cmd);
	}
	close(data()->here[1]);
	waitpid(pid, &status, 0);
	data()->in_heredoc = 0;
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		close(data()->here[0]);
		return (-1);
	}
	return (data()->here[0]);
}
