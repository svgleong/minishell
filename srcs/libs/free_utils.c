#include <minishell.h>

void    free_env_list(t_env **lst)
{
    t_env	*temp;
	
	while (*lst)
	{
		temp = (*lst)->next;
		free((*lst)->content);
		free((*lst));
		*lst = temp;
	}
	//*lst = NULL;
}

void	general_free(t_cmd *cmd, bool env, bool close_fds, bool to_exit)
{
	if (cmd)
		cmdlstclear(&cmd);
	if (env)
		free_env_list(&data()->envp);
	if (close_fds)
	{
		close(0);
		close(1);
		close(2);
	}
	if (to_exit)
		exit(data()->exit);
}
