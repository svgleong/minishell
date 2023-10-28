#include <minishell.h>

void	update_pwd(void)
{
	char	*path;
	t_env	*node;
	char	**var_value;
	char	*new_old_path;

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

void	cd(t_cmd *cmd)
{
	char	*path;

	if (cmd->args[1] == NULL)
	{
		path = getenv("HOME");
		if (path == NULL)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return ;
		}
	}
	else if (cmd->args[2] != NULL)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return ;
	}
	else
		path = cmd->args[1];
	if (chdir(path) == -1)
	{
		perror("Error");
		data()->exit = EXIT_FAILURE;
		return ;
	}
	update_pwd();
}
