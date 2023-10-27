#include <minishell.h>

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
        //line = search_expansion(cmd);
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
