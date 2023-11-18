/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 20:33:04 by svalente          #+#    #+#             */
/*   Updated: 2023/11/18 15:44:04 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	parser(char *rl)
{
	char	**tmp;

	if (!checker(rl))
		return (0);
	tmp = separate_args(rl);
	create_list(&data()->pointer_cmd, tmp);
	return (1);
}

void	error_empty_strs(char **args)
{
	ft_putstr_fd("ambiguous redirect\n", 2);
	free_matrix(args);
	data()->exit = 1;
}

int	create_list(t_cmd **lst, char **args)
{
	int	i;

	i = -1;
	while (args[++i])
	{
		if (args[i][0] != '|')
			cmd_add_back(lst, cmd_new_node(args + i++));
		while (args[i] && args[i][0] != '|')
			i++;
		if (!args[i])
			break ;
	}
	expander(lst);
	if (!remove_empty_strs(lst))
	{
		error_empty_strs(args);
		return (0);
	}
	free_matrix(args);
	check_redirections(lst);
	if (!redirections(lst))
		return (0);
	quote_checker(lst);
	return (1);
}
