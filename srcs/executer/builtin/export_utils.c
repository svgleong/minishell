#include <minishell.h>

char	*get_env_var(char *str)
{
	int		i;

	i = 0;
	while (str && str[i] && str[i] != '=')
		i++;
	return (ft_substr(str, 0, i));
}

/* void	print_export(char **export_env)
{
	int i;

	i = -1;
	char *env_var;
	while(export_env[++i])
	{
		env_var = get_env_var(export_env[i]);
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(env_var, STDOUT_FILENO);
		if (ft_strchr(export_env[i], '='))
		{
			ft_putchar_fd('\"', STDOUT_FILENO);
			ft_putstr_fd(ft_strchr(export_env[i], '=') + 1, STDOUT_FILENO);
			ft_putchar_fd('\"', STDOUT_FILENO);
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
		free(env_var);
	}
} */

void	print_export(char **export_env)
{
	char	*temp;
	int		i;
	int		j;

	i = -1;
	while (export_env[++i])
	{
		if (!ft_strncmp(export_env[i], "_=", 2))
			continue;

		temp = get_env_var(export_env[i]);
		printf("declare -x %s", temp);
		j = 0;
		while (temp[j])
			j++;
		if (export_env[i][j] == '=')
			printf("=\"%s\"\n", &export_env[i][j + 1]);
		else
			printf("\n");
		}
		free(temp);
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
