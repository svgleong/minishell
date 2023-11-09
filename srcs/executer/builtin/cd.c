#include <minishell.h>

void	update_pwd(void)
{
	char	*path;
	t_env	*node;
	char	**var_value;
	char	*new_old_path;

	if (search_env("OLDPWD") == NULL)
	{
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

void	ft_chdir(char	*path)
{
	if (chdir(path) == -1)
	{
		perror("Error");
		data()->exit = EXIT_FAILURE;
		free(path);
		return ;
	}
	free(path);
	update_pwd();
}

void	cd(t_cmd *cmd)
{
	char	*path;

	if (cmd->args[1] == NULL)
	{
		path = node_value(search_env("HOME"));
		if (path == NULL)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			free(path);
			return ;
		}
	}
	else
	{
		if (cmd->args[2] != NULL)
		{
			ft_putstr_fd("cd: too many arguments\n", 2);
			return ;
		}
		path = ft_strdup(cmd->args[1]);
	}
	ft_chdir(path);
}
