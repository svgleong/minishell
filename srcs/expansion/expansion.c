/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 13:02:23 by svalente          #+#    #+#             */
/*   Updated: 2023/11/13 19:21:42 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*expanding(char *str, char *value, int key, int i)
{
	char	*result;
	int		sz;
	int		f;
	int		k;

	sz = calculate_result(str, value, key, i);
	result = malloc(sz);
	f = -1;
	sz = -1;
	while (++f < i)
		result[f] = str[f];
	k = i + key + 1;
	while (value[++sz])
		result[i++] = value[sz];
	while (str[k])
		result[i++] = str[k++];
	result[i] = '\0';
	return (result);
}

char	*check_expansion(char *str, int *cursor)
{
	int	i;

	i = *cursor;
	if (!str[i + 1])
		return (ft_strdup(str));
	if (str[i + 1] == '\'' || str[i + 1] == '"')
		return (remove_dollar(str, cursor));
	if (str[i + 1] == '?')
		return ((get_status(str, cursor)));
	if (ft_isdigit(str[i + 1]))
		return (remove_character(str, cursor));
	if (str[i + 1] == '$')
		return (remove_dollar(str, cursor));
	if (!ft_isalnum(str[i + 1]) && str[i + 1] != '_')
		return (remove_character(str, cursor));
	return (expansion(str, cursor));
}

char	*expansion(char *str, int *cursor)
{
	char	*value;
	t_env	*env;
	int		i;

	i = *cursor;
	env = data()->envp;
	value = NULL;
	while (env)
	{
		if (!ft_strncmp(str + i + 1, env->content, \
			ft_strlen_special(env->content, '=')) && \
			key_value(str + i) == (int)ft_strlen_special(env->content, '='))
		{
			value = expanding(str, ft_strchr(env->content, '=') + 1, 
					ft_strlen_special(env->content, '='), i);
			(*cursor) += ft_strlen(ft_strchr(env->content, '=') + 1) - 1;
			return (value);
		}
		env = env->next;
	}
	value = remove_expand(str, cursor);
	(*cursor)--;
	return (value);
}

int	search_expansion(t_cmd *cmds)
{
	int		i;
	int		j;
	char	*tmp;
	bool	doub_quote;

	i = -1;
	while (cmds->args[++i])
	{
		j = -1;
		doub_quote = false;
		while (cmds->args[i][++j])
		{
			if (cmds->args[i][j] == '\'' && doub_quote == false)
				skip_quotes(cmds->args[i], '\'', &j);
			else if (cmds->args[i][j] == '"')
				doub_quote = !doub_quote;
			else if (cmds->args[i][j] && cmds->args[i][j] == '$')
			{
				tmp = check_expansion(cmds->args[i], &j);
				free(cmds->args[i]);
				cmds->args[i] = tmp;
			}
		}
	}
	return (0);
}

void	expander(t_cmd **cmds)
{
	t_cmd	*head;

	head = *cmds;
	while (*cmds)
	{
		search_expansion(*cmds);
		(*cmds) = (*cmds)->next;
	}
	(*cmds) = head;
}

//echo "'$USER'"'"$USER"'
//echo '"$USER"'"'$USER'"