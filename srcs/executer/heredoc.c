#include <minishell.h>

void    child_heredoc(t_cmd *cmd, int fds[2])
{
    char *line;

    while (1)
    {
        write(0, "> ", 2);
        line = get_next_line(0);
        if (!line || !ft_strncmp(line, cmd->redir->file, ft_strlen(cmd->redir->file)))
        {
            free(line);
            break;
        }
        write(fds[1], line, ft_strlen(line));
        free(line);
    }
    close(fds[1]);
    exit(0);
}

int heredoc(t_cmd *cmd)
{
    int fds[2];
    int pid;

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
