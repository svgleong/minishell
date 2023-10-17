//export manages variables to call them or write them to export them
// export with no args to export to for example another shell
// normally stdin stdout but can pipe to file
// uses builtin declare that we dont create but in bash there is
//declare -x A[="B"] -> can declare NULL / "\0" / abc
////
//
// export is sorted alphabetacly and has declare -x


#include <executer.h>

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

int valid_conditions(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void update(char *new_value)
{
	t_env *ptr = data()->envp;
	char *cmd_var = get_env_var(new_value);
	char *env_var;
	while (ptr && ptr->content)
	{
		env_var = get_env_var(ptr->content);
		if (ft_strncmp(cmd_var, env_var, ft_strlen(cmd_var)) == 0)
		{
			free(ptr->content);
			ptr->content = ft_strdup(new_value);
			free(env_var);
			free(cmd_var);
			return ;
		}
		ptr = ptr->next;
		free(env_var);
	}
	free(cmd_var);
}

void	export_bi(t_cmd *cmd)
{
	char **export_env;
	int i;

	i = 0;
	printf("Entrou export\n");
	export_env = env_to_matrix();
	if (!(cmd->args[1]))
	{
		bubble_sort(export_env);
		print_export(export_env);
		free_matrix(export_env);
	}
	else
	{
		while (cmd->args[++i])
		{
			if (valid_conditions(cmd->args[i]) == 0)
				write(2, ": invalid conditions\n", 21);
			else
				update(cmd->args[i]);
		}
	}
}
