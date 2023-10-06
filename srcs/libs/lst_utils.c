#include <minishell.h>

int	list_size(void)
{
	int i = 0;

	while(data()->envp)
	{
		data()->envp = data()->envp->next;
		i++;
	}
	return (i);
}

char **env_to_matrix(void)
{
	int len = list_size();
	char **matrix;
	int i = 0;
	matrix = malloc(sizeof(char *) * (len+1));
	if (!matrix)
		return (NULL);
	while (data()->envp)
	{
		matrix[i] = ft_strdup(data()->envp->content);
		data()->envp = data()->envp->next;
		i++;
	}
	matrix[i] = NULL;
	return (matrix); 
}