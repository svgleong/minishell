/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:41:19 by svalente          #+#    #+#             */
/*   Updated: 2023/11/03 12:45:30 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* void	remove_quotes(t_cmd **cmds)
{
	char	*tmp;
	int		i;
	t_cmd	*head;

	tmp = NULL;
	head = *cmds;
	while ((*cmds))
	{
		i = -1;
		while ((*cmds)->args[++i])
		{
			if ((*cmds)->args[i][0] == '\'' || (*cmds)->args[i][0] == '\"')
			{
				tmp = ft_substr((*cmds)->args[i], 1, \
					ft_strlen((*cmds)->args[i]) - 2);
				free((*cmds)->args[i]);
				(*cmds)->args[i] = tmp;
			}
		}
		(*cmds) = (*cmds)->next;
	}
	(*cmds) = head;
} */

char *rem_quotes_pair(char *arg, char quote, int *j)
{
	char	*new_str;
	int		i;
	int		tmp;

	i = -1;
	new_str = malloc(ft_strlen(arg) - 1);
	while (++i < *j)
		new_str[i] = arg[i];
	// printf("%s\n", new_str);
	(*j)++;
	while (arg[(*j)] != quote)
	{
		new_str[i] = arg[(*j)];
		(*j)++;
		i++;
	}
	// printf("%s\n", new_str);
	
	tmp = (*j);
	while (++tmp < (int)ft_strlen(arg))
	{
		new_str[i] = arg[tmp];
		i++;
	}
	(*j) = (*j) - 2;
	new_str[i] = '\0';
	//printf("New str: %s\n", new_str);
	//printf("j index = %d\n", (*j));
	free(arg);
	return (new_str);
}


	
void remove_quotes(char **args)
{
	// Verificat a quote
	// Procurar a quote que da match
	// Remover ambas
	// Guardar iterador no match quote para iterar a partir desse momento
	int		i;
	int		j;

	i = -1;
	while (args[++i])
	{
		j = -1;
		while (args[i][++j])
		{
			if (args[i][j] == '\'')
				args[i] = rem_quotes_pair(args[i], '\'', &j);
			else if (args[i][j] == '"')
				args[i] = rem_quotes_pair(args[i], '"', &j);
			if (j >= (int)ft_strlen(args[i]))
				break ;
		}
	}
}
void	quote_checker(t_cmd **cmd)
{
	t_cmd *head;

	head = *cmd;
	while (*cmd)
	{
		remove_quotes((*cmd)->args);
		(*cmd) = (*cmd)->next;
	}
	(*cmd) = head;
}	
