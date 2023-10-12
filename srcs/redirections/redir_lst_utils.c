/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_lst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 12:22:56 by svalente          #+#    #+#             */
/*   Updated: 2023/10/12 12:43:36 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_redir *redir_new_node(int redir, char *file)
{
    t_redir *new;

    printf("new node\n");
    new = ft_calloc(1, sizeof(t_redir));
    if (!new)
        return (NULL);
    new->fd = -1;
    new->redir = redir;
	new->file = file;
    new->next = NULL;
    return (new);
}

t_redir *redir_last_node(t_redir *lst)
{
    if (!lst)
        return (NULL);
    while (lst->next)
        lst = lst->next;
    return (lst);
}

void    redir_add_back(t_redir **lst, t_redir *new)
{
    t_redir	*last;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = redir_last_node(*lst);
	last->next = new;
}

void	create_redir_lst(t_cmd **cmd, int redir, char *file)
{
	printf("%s\n", file);
	redir_add_back(&(*cmd)->redir, redir_new_node(redir, file));
}

void    print_redir(t_redir *lst)
{
    t_redir *tmp = lst;

    if (!lst)
    {
		printf("Empty list2\n");	
		return ;
	}
    while (tmp)
    {
        printf("redir: %d\n", tmp->redir);
        printf("file: %s\n", tmp->file);
        tmp = tmp->next;
    }
}
void	check_redirections(t_cmd **cmds)
{
	t_cmd	*head;
	int		i;

	head = (*cmds);
	i = -1;
	while ((*cmds))
	{
		while ((*cmds)->args[++i])
		{
			if (!ft_strncmp((*cmds)->args[i], ">>", 2))
            {
                create_redir_lst(cmds, 2, (*cmds)->args[i + 1]);
            }
		}
        (*cmds) = (*cmds)->next;
	}
    (*cmds) = head;
    print_redir((*cmds)->redir);
}
