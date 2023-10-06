/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 13:02:23 by svalente          #+#    #+#             */
/*   Updated: 2023/10/06 18:11:01 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	key_value(char *str)
{
	int	sz;

	sz = 0;
	while (str[++sz] && ft_isalnum(str[sz]))
		;
	return (sz -1);
}

char	*expanding(char *str, char *value, int key)
{
	char	*result;
	int		sz;
	int		i;
	int		k;

	sz = calculate_result(str, value, key);
	result = malloc(sz);
	i = -1;
	sz = -1;
	while (str[++i] != '$')
		result[i] = str[i];
	k = i + key + 1;
	while (value[++sz])
		result[i++] = value[sz];
	while (str[k])
		result[i++] = str[k++];
	result[i] = '\0';
	return (result);
}

char	*check_expansion(char *str, int i)
{
	if (!str[i + 1])
		return ("\2");
	if (str[i + 1] == '?')
		return ((str = get_status(str, i)));
	if (ft_isdigit(str[i + 1]))
		return (remove_number(str, i));
	if (str[i + 1] == '$')
		return (remove_dollar(str, i));
	if (!ft_isalnum(str[i + 1]))
		return ("\2");
	return (expansion(str, i));
}

char	*expansion(char *str, int i)
{
	t_env	*env;

	env = data()->envp;
	value = NULL;
	while (env)
	{
		if (!ft_strncmp(str + i + 1, env->content, \
			ft_strlen_special(env->content, '=')) && \
			key_value(str + i) == (int)ft_strlen_special(env->content, '='))
		{
			value = expanding(str, ft_strchr(env->content, '=') + 1, 
					ft_strlen_special(env->content, '='));
			return (value);
		}
		env = env->next;
	}
	value = remove_expand(str);
	return (value);
}

int	search_expansion(t_cmd *cmds)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	j = -1;
	while (cmds->args[++i])
	{
		j = -1;
		while (cmds->args[i][++j])
		{
			if (cmds->args[i][0] == '\'')
				break ;
			else if (cmds->args[i][j] && cmds->args[i][j] == '$')
			{
				tmp = check_expansion(cmds->args[i], j);
				if (tmp[0] == '\2')
					continue ;
				free(cmds->args[i]);
				cmds->args[i] = tmp;
				j = -1;
			}
		}
	}
	return (0);
}
