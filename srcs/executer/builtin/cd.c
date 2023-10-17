#include <minishell.h>

void update_pwd(t_cmd *cmd)
{
    (void)cmd;
    write(2, "need to update\n", 16);
}

void cd(t_cmd *cmd)
{
    char *path;

    if (cmd->args[1] == NULL) 
    {
        path = getenv("HOME");
        if (path == NULL) 
        {
            write(2, "cd: HOME not set\n", 17);
            return ;
        }
    }
    else if (cmd->args[2] != NULL) {
        write(2, "cd: too many arguments\n", 23);
        return ;
    } 
    else 
        path = cmd->args[1];
    if (chdir(path) == -1) {
        perror("Error:");
        return ;
    }
    update_pwd(cmd);
}