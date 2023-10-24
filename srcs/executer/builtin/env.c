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

/* void    free_env_list(t_env **lst)
{
    t_env	*temp;
	
	while (*lst)
	{
		temp = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = temp;
	}
} */

void    free_env_list(t_env **lst)
{
    t_env	*temp;
	
	while (*lst)
	{
		temp = (*lst);
		(*lst) = (*lst)->next;
		//printf("content: %s\n", temp->content);
		free(temp->content);
		free(temp);
	}
	*lst = NULL;
}

//find last node in list
t_env	*env_last_node(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
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
	return (new);
}

//puts char **env to list
void	get_env_to_list(char **env)
{
	int i = 0;
	data()->redir = 0;
	data()->envp = env_new_node(env[0]);
	while (env[++i])
		env_add_node_end(data()->envp, env_new_node(env[i]));
}

void    envp()
{
    t_env *env = data()->envp;
	while (env && env->content)
	{
		if (ft_strchr(env->content, '=') && ft_strncmp(env->content, "_", 1))
			printf("%s\n", env->content);
		env = env->next;
	}
}

