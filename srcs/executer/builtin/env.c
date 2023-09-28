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
void	env_add_node_end(t_env **lst, t_env *new)
{
	if (lst)
	{
		if (*lst)
		{
			new->prev = env_last_node(*lst);
			env_last_node(*lst)->next = new;
		}
		else
			*lst = new;
	}
}

//creates and allocs new node putting env str in content
t_env	*env_new_node(char *str)
{
	t_env	*new;

	new = ft_calloc(sizeof(t_env), 1);
	if (!new)
		return (NULL);
	new->content = ft_strdup(str);
		//printf("content %s\n", new->content);
	return (new);
}

//puts char **env to list
t_env	*get_env_to_list(char **env)
{
	t_env	*env_list = NULL;

	int i = -1;
	while (env[++i])
		env_add_node_end(&env_list, env_new_node(env[i]));
    return (env_list);
}

void	print_env(t_env *env)
{
	if (!env)
		printf("nada\n");
	while (env)
	{
		printf("%s\n", env->content);
		env = env->next;
	}
}

void    env_bi(char **env, t_env *env_lst)
{
	env_lst = get_env_to_list(env);
    print_env(env_lst);
    free_env_list(&env_lst);
}

