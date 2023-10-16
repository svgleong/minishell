#include <minishell.h>

/* void    main_loop(char *delimiter, int fd)
{
    char *line;
    while (1)
    {
        line = readline("> ");
        if (!ft_strncmp(line, delimiter, ft_strlen(delimiter)))
            break ;
        write(fd, line, ft_strlen(line));
        write(fd, "\n", 1);
        free(line);
    }
    free(line);
} */

/* void child_here_doc(int fd[2], t_cmd *cmd)
{
    sigal(SIGQUIT, SIG_IGN);
    close(fd[0]);
    main_loop(cmd->args[1], fd[1]);
    close(fd[1]);
    exit(0);
} */

/* void    parent_here_doc(int fd[2], t_cmd *cmd)
{
    signal(SIGINT, SIG_IGN);
    wait(exit_status);
    close(fd[1]);
    if (WIFEXITED(exit_status))
	{
		exit_status = WEXITSTATUS(exit_status);
		if (exit_status == 1)
			return (-3);
		else
			command->std_in = dup(heredoc[0]);
		close(heredoc[0]);
	}
	signals_init();
	return (0);
} */

/* int get_here_doc(t_cmd *cmd)
{
    int pid;
    int fd[2];
    if (pipe(fd) == -1)
        return (-1);
    pid = fork();
    if (pid == -1)
        return (-1);
    if (pid == 0)
        child_here_doc(fd, cmd);
    if (pid > 0)
        return (parent_here_doc(fd, cmd));
    return (0);
} */