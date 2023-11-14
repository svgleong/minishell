/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:41:19 by svalente          #+#    #+#             */
/*   Updated: 2023/11/14 22:06:27 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*allocate_new_str(char *arg)
{
	char	*new_str;

	new_str = malloc(ft_strlen(arg) - 1);
	if (!new_str)
		general_free(data()->pointer_cmd, 1, 0, 1);
	return (new_str);
}

char	*rem_quotes_pair(char *arg, char quote, int *j)
{
	char	*new_str;
	int		i;
	int		tmp;

	i = -1;
	new_str = allocate_new_str(arg);
	while (++i < *j)
		new_str[i] = arg[i];
	(*j)++;
	while (arg[(*j)] != quote)
	{
		new_str[i] = arg[(*j)];
		(*j)++;
		i++;
	}
	tmp = (*j);
	while (++tmp < (int)ft_strlen(arg))
	{
		new_str[i] = arg[tmp];
		i++;
	}
	(*j) = (*j) - 2;
	new_str[i] = '\0';
	free(arg);
	return (new_str);
}

void	remove_quotes(char **args)
{
	int		i;
	int		j;

	i = -1;
	while (args[++i])
	{
		j = -1;
		while (args[i][++j])
		{
			if (args[i][j + 1] && args[i][j] == '<' && args[i][j + 1] == '<' )
			{
				i++;
				break ;
			}
			else if (args[i][j] == '\'')
				args[i] = rem_quotes_pair(args[i], '\'', &j);
			else if (args[i][j] == '"')
				args[i] = rem_quotes_pair(args[i], '"', &j);
			if (j >= (int)ft_strlen(args[i]))
				break ;
		}
	}
}

char	*remove_quotes_redir(char *args)
{
	int		j;

	j = -1;
	while (args[++j])
	{
		if (args[j] == '\'')
			args = rem_quotes_pair(args, '\'', &j);
		else if (args[j] == '"')
			args = rem_quotes_pair(args, '"', &j);
	}
	return (args);
}

void	quote_checker_file(t_cmd **cmd)
{
	t_cmd	*head;
	t_redir	*head_redir;
	char	*tmp;

	head = *cmd;
	while (*cmd)
	{
		head_redir = (*cmd)->redir;
		while ((*cmd)->redir)
		{
			tmp = (*cmd)->redir->file;
			(*cmd)->redir->file = remove_quotes_redir((*cmd)->redir->file);
			free(tmp);
			(*cmd)->redir = (*cmd)->redir->next;
		}
		(*cmd)->redir = head_redir;
		(*cmd) = (*cmd)->next;
	}
	(*cmd) = head;
}

void	quote_checker(t_cmd **cmd)
{
	t_cmd	*head;

	head = *cmd;
	while (*cmd)
	{
		remove_quotes((*cmd)->args);
		(*cmd) = (*cmd)->next;
	}
	(*cmd) = head;
}

int	skip_quotes(char *str, char quote, int *i)
{
	if (!str[++(*i)])
		return (-1);
	while (str[*i])
	{
		if (str[*i] == quote)
			return (1);
		(*i)++;
	}
	return (-1);
}
