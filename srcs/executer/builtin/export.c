//export manages variables to call them or write them to export them
// export with no args to export to for example another shell
// normally stdin stdout but can pipe to file
// uses builtin declare that we dont create but in bash there is
//declare -x A[="B"] -> can declare NULL / "\0" / abc
//

#include "../includes/executer.h"

/* Esta funcao retorno o ultimo elemento de uma lista do tipo t_env */
t_env	*ft_envlast(t_env *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

/* Adiciona um novo elemento a uma lista t_env */
void	ft_envadd_back(t_env **lst, t_env *new)
{
	if (lst)
	{
		if (*lst)
		{
			new->prev = ft_envlast(*lst);
			ft_envlast(*lst)->next = new;
		}
		else
			*lst = new;
	}
}

t_env	*ft_envnew(char *str)
{
	t_env	*new;

	new = (t_env *)ft_calloc(sizeof(t_env), 1);
	if (!new)
		return (NULL);
	new->content = str;
	return (new);
}

t_env	*get_env_to_list(char **env)
{
	t_env	*env_list = NULL;

	int i = -1;
	while (env[++i])
		ft_envadd_back(&env_list, ft_envnew(ft_strdup(env[i])));
}

char **env_to_struct(t_env **env)
{
	int size;

	size = env_len(env);
}