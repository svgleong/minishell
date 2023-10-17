//export manages variables to call them or write them to export them
// export with no args to export to for example another shell
// normally stdin stdout but can pipe to file
// uses builtin declare that we dont create but in bash there is
//declare -x A[="B"] -> can declare NULL / "\0" / abc
////
//
// export is sorted alphabetacly and has declare -x


#include <executer.h>

int	check_export_conditions(char *str)
{
	int	i;

	if (!(ft_isalpha(str[0]) || str[0] == '_'))
		return (0);
	i = 0;
	while (str[++i] && str[i] != '=')
	{
		if (!(ft_isalpha(str[i]) || ft_isdigit(str[i] || str[i] == '_')))
			return (0);
	}
	return (1);
}

char	*get_env_var(char *str)
{
	int		i;

	i = 0;
	while (str && str[i] && str[i] != '=')
		i++;
	return (ft_substr(str, 0, i));
}

void	print_export(char **export_env)
{
	int i;

	i = -1;
	while(export_env[++i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(get_env_var(export_env[i]), STDOUT_FILENO);
		if (ft_strchr(export_env[i], '='))
		{
			ft_putchar_fd('\"', STDOUT_FILENO);
			ft_putstr_fd(ft_strchr(export_env[i], '=') + 1, STDOUT_FILENO);
			ft_putchar_fd('\"', STDOUT_FILENO);
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
}

void bubble_sort(char **matrix)
{
	int i;
	int j;
	char *temp;
	int size = 0;

	while (matrix[size])
		size++;
	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp(matrix[j], matrix[j + 1]) > 0)
			{
				temp = matrix[j];
				matrix[j] = matrix[j + 1];
				matrix[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}
size_t	var_size(char *env_str)
{
	int	i;

	i = 0;
	while (env_str[i] && env_str[i] != '=')
		i++;
	return (i);
}

t_env	*find_env_var(char *cmd)
{
	t_env *temp;

	temp = data()->envp;
	while (temp && temp->content)
	{
		if (!temp)
			break;
		if (!ft_strncmp(temp->content, cmd, ft_strlen(cmd)) && var_size(temp->content) == ft_strlen(cmd))
			return (temp);
		if (!temp->next)
			break;
		temp = temp->next;
	}
	return (NULL);
}

void	update_export_env(char *cmd, char **new_var)
{
	t_env *var_in_env;

	var_in_env = find_env_var(new_var[0]);
	if (!var_in_env)
		env_add_node_end(data()->envp, env_new_node(ft_strdup(cmd)));
	else
	{
		if (cmd[1])
		{
			free(var_in_env->content);
			var_in_env->content = ft_strdup(cmd);
		}
	}
}




void	export_bi(t_cmd *cmd)
{
	char **export_env;
	int i;

	i = 1;
	export_env = env_to_matrix();
	if (!(cmd->args[1]))
	{
		bubble_sort(export_env);
		print_export(export_env);
		free_matrix(export_env);
	}
	else
	{
		while (cmd->args[i])
		{
			if (!check_export_conditions(cmd->args[i]))
			{
				write(STDERR_FILENO, " not a valid identifier\n", 24);
				return ;
			}
			free_matrix(export_env);
			export_env = ft_split(cmd->args[i], '=');
			update_export_env(cmd->args[i], export_env);
		}
	}
}
