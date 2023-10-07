#include "../includes/executer.h"

//frees list
/* void    free_env_list(t_env *env)
{
    t_env   *tmp;
    while (env)
    {
        tmp = (env)->next;
        free((env)->content);
        free(env);
        env = tmp;
    }
} */

void    free_env_list(t_env **lst)
{
    t_env	*temp;

		while (*lst)
		{
			temp = (*lst)->next;
			free((*lst)->content);
			free(*lst);
			*lst = temp;
		}
}

//find last node in list
t_env	*env_last_node(t_env *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

//adds the created node in the last position
void	env_add_node_end(t_env *lst, t_env *new)
{
	if (lst)
	{
		new->prev = env_last_node(lst);
		env_last_node(lst)->next = new;
	}
	else
		lst = new;
}

//creates and allocs new node putting env str in content
t_env	*env_new_node(char *str)
{
	t_env	*new;

	new = ft_calloc(sizeof(t_env), 1);
	if (!new)
		return (NULL);
	new->content = ft_strdup(str);
	new->prev = NULL;
	new->next = NULL;
	//printf("content %s\n", new->content);
	return (new);
}

//puts char **env to list
void	get_env_to_list(char **env)
{
	int i = 0;
	data()->envp = env_new_node(env[0]);
	while (env[++i])
		env_add_node_end(data()->envp, env_new_node(env[i]));
}

void	print_env()
{
	t_env *env = data()->envp;
 
	if (!env)
		printf("nada\n");
	while (env)
	{
		printf("%s\n", env->content);
		env = env->next;
	}
}

void    env_builtin(t_cmd *cmd)
{
	(void)cmd;
    print_env();
}

