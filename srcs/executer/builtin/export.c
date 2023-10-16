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

void	export_bi(t_cmd *cmd)
{
	char **export_env = env_to_matrix();
	if (!(cmd->args[1]))
	{
		bubble_sort(export_env);
		print_export(export_env);
		free_matrix(export_env);
	}
}
