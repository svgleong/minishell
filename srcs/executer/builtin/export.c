// export manages variables to call them or write them to export them
//  export with no args to export to for example another shell
//  normally stdin stdout but can pipe to file
//  uses builtin declare that we dont create but in bash there is
// declare -x A[="B"] -> can declare NULL / "\0" / abc
////
//
// export is sorted alphabetacly and has declare -x

#include <executer.h>

t_env	*search_env(char *var)
{
	t_env	*envp;

	envp = data()->envp;
	while (envp && envp->content != NULL)
	{
		if (!ft_strncmp(envp->content, var, ft_strlen_special(envp->content, '=')))
			return (envp);
		envp = envp->next;
	}
	return (NULL);
}

void	update_env_export(char *cmd, char **new_var)
{
	t_env	*node;
	char	*var;
	char	*value;

	var = new_var[0];
	value = new_var[1];
	node = search_env(var);
	if (node == NULL)
		env_add_node_end(data()->envp, env_new_node(cmd));
	if (node && value)
	{
		free(node->content);
		node->content = ft_strdup(cmd);
	}
}

int	verify_export(t_cmd *cmd)
{
	int i;

	i = -1;
	while (cmd->args[++i])
	{
		if (is_valid(cmd->args[i]) == 0)
		{
			ft_putstr_fd("not a valid identifier\n", STDERR_FILENO);
			data()->exit = EXIT_FAILURE;
			return (0);
		}
	}
	return (1);
}

void	normal_export(t_cmd *cmd, int i)
{
	char	**var_value;

	//print_list(cmd);
	if (verify_export(cmd) == 0)
		return ;
	while (cmd->args[++i])
	{
		var_value = ft_split(cmd->args[i], '=');
		update_env_export(cmd->args[i], var_value);
		free_matrix(var_value);
	}
}

void	export(t_cmd *cmd)
{
	int		i;
	char	**export_env;

	i = 0;
	export_env = NULL;
	//print_list(cmd);
	if (!(cmd->args[1]))
	{
		export_env = env_to_matrix();
		bubble_sort(export_env);
		print_export(export_env);
		free_matrix(export_env);
		data()->exit = EXIT_SUCCESS;
		return ;
	}
	else
		normal_export(cmd, i);
}
