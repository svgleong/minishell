#include <minishell.h>

char	**env_to_matrix()
{
	int		len;
	char	**matrix;
	t_env	*temp;

	len = 0;
	temp = (t_env *)data()->envp;
	while (temp)
	{
		len++;
		temp = temp->next;
	}
	matrix = malloc(sizeof(char *) * (len + 1));
	if (!matrix)
		return (NULL);
	temp = (t_env *)data()->envp;
	len = 0;
	while (temp)
	{
		matrix[len] = ft_strdup(temp->content);
		if (!matrix[len])
			return (NULL);
		temp = temp->next;
		len++;
	}
	matrix[len] = NULL;
	return (matrix);
}