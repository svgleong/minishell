#include <minishell.h>

/* void update_pwd(t_env *node)
{
    char *path;
    char **var_value;
    if (!node)
    {
        path = ft_strjoin_free("OLDPWD=", getcwd(NULL, 0), 2);
        env_add_node_end(data()->envp, env_new_node(path));
    }
    else
    {
        var_value = ft_split(node->content, '=');
        if (!ft_strcmp(var_value[0], "OLDPWD"))
        {
            free(node->content);
            path = ft_strjoin_free("OLDPWD=", getcwd(NULL, 0), 2);
            node->content = path;
        }
        else
        {
            free(node->content);
            path = ft_strjoin_free("PWD=", getcwd(NULL, 0), 2);
            node->content = path;
        }
    }
} */

void    update_pwd(void)
{
    char *path;
    t_env *node;
    char **var_value;
    char *new_old_path;
    if (search_env("OLDPWD") == NULL)
    {
        printf("NOT OLDPWD\n");
        path = ft_strjoin_free("OLDPWD=", getcwd(NULL, 0), 2);
        env_add_node_end(data()->envp, env_new_node(path));
        free(path);
    }
    node = search_env("PWD");
    var_value = ft_split(node->content, '=');
    new_old_path = ft_strjoin_free("OLDPWD=", var_value[1], 0);
    free(node->content);
    path = ft_strjoin_free("PWD=", getcwd(NULL, 0), 2);
    node->content = path;
    node = search_env("OLDPWD");
    free(node->content);
    node->content = new_old_path;
    free_matrix(var_value);
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
            data()->exit = EXIT_FAILURE;
            return ;
        }
    }
    else if (cmd->args[2] != NULL) {
        write(2, "cd: too many arguments\n", 23);
        data()->exit = EXIT_FAILURE;
        return ;
    }
    else 
        path = cmd->args[1];
    if (chdir(path) == -1) {
        perror("Error");
        data()->exit = EXIT_FAILURE;
        return ;
    }
    update_pwd();
    data()->exit = EXIT_SUCCESS;
}