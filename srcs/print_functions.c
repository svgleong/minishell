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

void	print_matrix(char **m)
{
	int	i;

	i = 0;
	if (!m)
		return ;
	while (m[i])
	{
		printf("[%s]\n", m[i]);
		i++;
	}
	printf("\n");
}

void	print_redir(t_redir *lst)
{
	t_redir *tmp = lst;

	if (!lst)
	{
		printf("Empty list for redirections\n");	
		return ;
	}
	while (tmp)
	{
		// printf("Address of red: %p\n", tmp);
		// printf("Address of file: %p\n", tmp->file);
		printf("redir: %d\n", tmp->redir);
		printf("file: %s\n", tmp->file);
		tmp = tmp->next;
	}
}