#include <minishell.h>

void	free_fds()
{
	close(0);
	close(1);
	close(2);
}

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