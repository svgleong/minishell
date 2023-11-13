#include <minishell.h>

void	print_list(t_cmd *lst)
{
	t_cmd	*tmp = lst;
	int i = 0;
	int j = 1;
	if(!lst)
	{
		printf("Empty list\n");	
		return ;
	}
	while (tmp)
	{
		printf("--------------[NODE %d]\n", j);
		i = 0;
		if (!tmp->args || !tmp->args[0])
			printf("No arguments\n");
		while (tmp->args[i])
		{
			printf("arg[%d] [%s]\n", i, tmp->args[i]);
			i++;
		}
		printf("==============\n");
		print_redir(tmp->redir);
		printf("==============\n");
		printf("fd_in: %d\n", tmp->fd_in);
		printf("fd_out: %d\n", tmp->fd_out);
		tmp = tmp->next;
		j++;
	}
	printf("---------------------\n");
}
