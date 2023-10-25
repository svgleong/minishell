#include <minishell.h>

/* int    main_loop(char *delimiter, int fd)
{
    char *line;
    while (1)
    {
        write(0, " >", 2);
        line = get_next_line(0);
        if (!ft_strncmp(line, delimiter, ft_strlen(delimiter)))
            break ;
        if (!line)
            return (-1);
        write(fd, line, ft_strlen(line));
        write(fd, "\n", 1);
        free(line);
    }
    free(line);
    return (0);
} */

void	ft_handler(int sig)
{
	if (sig == SIGINT)
	{
		data()->exit = 130;
		/* if (shell()->in_exec == true)
		{
			printf("\n");
			return ;
		} */
		ft_putstr_fd("^C\n", 0);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	/* else if (sig == SIGQUIT)
	{
		if (shell()->in_exec == true)
		{
			shell()->exit_code = 131;
			ft_putstr_fd("Quit: 3\n", 2);
		}
	} */
}

void    handle_signals(void)
{
    signal(SIGINT, ft_handler);
    signal(SIGQUIT, ft_handler);
}

void	heredoc_error(char *str)
{
	printf("\nWarning: heredoc on line 1 delimited by EOF (wanted: \"%s\")\n", str);
	handle_signals();
}

void    child_heredoc(t_cmd *cmd, int *fds)
{
    char *line = NULL;
    int i = 0;

    signal(SIGINT, SIG_IGN);
    while (cmd->args && cmd->args[i])
    {
        while (1)
        {
            write(0, "> ", 2);
            line = get_next_line(0);
            if (!line)
            {
                close(fds[1]);
                close(fds[0]);
                exit(-1);
                //tratar de frees
            }
            if (!(ft_strncmp(line, cmd->args[i], ft_strlen(cmd->args[i]))))
            {
                free(line);
                break;
            }
            if (cmd->args[i + 1] == NULL)
            {
                write(fds[1], line, ft_strlen(line));
            }
            free(line);
            line = NULL;
        }
        i++;
    }
}

int    heredoc(t_cmd *cmd)
{
    int fds[2];
    int pid;
    print_list(cmd);
    signal(SIGQUIT, SIG_IGN);
    if (pipe(fds) == -1)
        perror("");
    pid = fork();
    if (pid == 0)
        child_heredoc(cmd, fds);
    close(fds[1]);
    wait(&pid);
    return (fds[0]);
}