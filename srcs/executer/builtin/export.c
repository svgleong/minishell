//export manages variables to call them or write them to export them
// export with no args to export to for example another shell
// normally stdin stdout but can pipe to file
// uses builtin declare that we dont create but in bash there is
//declare -x A[="B"] -> can declare NULL / "\0" / abc
////
//
// export is sorted alphabetacly and has declare -x


#include <executer.h>

t_env	*search_env(char *var)
{
	t_env *envp;

	envp = data()->envp;
	while (envp && envp->content != NULL)
	{
		if (!ft_strncmp(envp->content, var, ft_strlen(var)))
			return (envp);
		envp = envp->next;
	}
	return (NULL);
}

void	update_env_export(char *cmd, char **new_var)
{
	t_env *node;
	char *var;
	char *value;

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

int is_valid(char *var)
{
	int		i;

	i = 0;
	if (ft_isdigit(var[i]) || var[0] == '_')
		return (0);
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) || var[i] == '_')
			return (0);
		i++;
	}
	return (1);
}

char *rem_quotes_export(char *s)
{
	int i = 0;
	int j = 0;
	char *new;

	new = malloc(sizeof(char) * ft_strlen(s)+1);
	while (s[i])
	{
		if (s[i] != '\"')
		{
			new[j] = s[i];
			j++;
		}
		i++;
	}
	new[j] = '\0';
	return (new);
}


void	export(t_cmd *cmd)
{
	char **export_env = NULL;
	int i = 0;
	char **var_value;
	char *temp;
	if (!(cmd->args[1]))
	{
		export_env = env_to_matrix();
		bubble_sort(export_env);
		print_export(export_env);
		free_matrix(export_env);
		return ;
	}
	else
	{
		while (cmd->args[++i])
		{
			if (is_valid(cmd->args[i]) == 0)
				printf("option not valid\n");
			else
			{
				temp = rem_quotes_export(cmd->args[i]);
				var_value = ft_split(cmd->args[i], '=');
				update_env_export(temp, var_value);
				//printf("%s\n", cmd->args[i]);
				free(temp);
				free_matrix(var_value);
			}
		}
	}
}
