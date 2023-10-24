#include <minishell.h>

void update_pwd(t_env *node)
{
    //encontrar o atual e guardar no old
    //pegar no novo e guardar no atual
    char **str = ft_split(node->content, '=');
    if (ft_strncmp(str[0], "OLDPWD", 6) == 0)
        node->content = ft_strjoin_free("OLDPWD=", str[1], 2);
    else if (ft_strncmp(str[0], "PWD", 3))
    {
        node->content = ft_strjoin_free("PWD=", getcwd(NULL, 0), 2);
    }

}

void cd(t_cmd *cmd)
{
    char *path;

    update_pwd(search_env("OLDPWD"));
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
    update_pwd(search_env("PWD"));
}