/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 13:02:23 by svalente          #+#    #+#             */
/*   Updated: 2023/10/06 12:57:39 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_status(char *str, int i)
{
	(void)str;
	(void)i;
	return NULL;
}

int	calculate_result(char *str , char *value, int key)
{
	if (!value)
		return (ft_strlen_special(str, '$') + ft_strlen(ft_strchr(str, '$') + key));
	return (ft_strlen_special(str, '$') + ft_strlen(value) + \
	ft_strlen(ft_strchr(str, '$') + key));
}

char	*expanding(char *str , char *value, int key) 
{
	char	*result;
	int		sz;
	int		i;
	int		k;

	sz = calculate_result(str, value, key);
	//printf("sz: %d\n", sz);
	result = malloc(sz);
	i = -1;
	sz = -1;
	while (str[++i] != '$')
		result[i] = str[i];
	k = i  + key + 1;
	while (value[++sz])
		result[i++] = value[sz];
	while (str[k])
		result[i++] = str[k++];
	result[i] = '\0';
	printf("result %s\n", result);
	return (result);
}

int	key_value(char *str)
{
	int	sz;

	sz = 0;
	while (str[++sz] && ft_isalnum(str[sz]))
		;
	return (sz -1);
}

char	*remove_expand(char *str)
{
	char	*new_str;
	int		sz;
	int		key;
	int		i;
	
	key = key_value(ft_strchr(str, '$'));
	sz = calculate_result(str, NULL, key);
	new_str = malloc(sz);
	sz = -1;
	while (str[++sz] && str[sz] != '$')
		new_str[sz] = str[sz];
	i = sz + key + 1;
	while (str[i])
	{
		new_str[sz++] = str[i];
		i++;
	}
	new_str[sz] = '\0';
	return (new_str);
}

char	*expansion(char *str, int i)
{
	t_env	*env;
	char	*value;

	env = data()->envp;
	value = NULL;

	if (!str[i + 1])
		return "\2";
	if (str[i + 1] == '?')
		return ((str = get_status(str, i)));
	while (env)
	{
		if (!ft_strncmp(str + i + 1, env->content, ft_strlen_special(env->content, '=')))
		{
			value = expanding(str, ft_strchr(env->content, '=') + 1, ft_strlen_special(env->content, '='));
			return (value);
		}
		env = env->next;
	}
	if (!ft_isalnum(str[i + 1]))
		return "\2";
	value = remove_expand(str);
	return (value);
}

int	search_expansion(t_cmd *cmds)
{
	int		i;
	int		j;
	char	*tmp;
	//char	*str;

	i = -1;
	j = -1;
	while (cmds->args[++i])
	{
		j = -1;
		while  (cmds->args[i][++j])
		{
			if (cmds->args[i][0] == '\'')
				break ;
			else if (cmds->args[i][j] && cmds->args[i][j] == '$')
			{
				tmp = expansion(cmds->args[i], j);
				if (tmp[0] == '\2')
					continue ;
				free(cmds->args[i]);
				cmds->args[i] = tmp;
				//printf("cmd: %s\n", cmds->args[i]);
				j = -1;
				//(void)tmp;
				// $+USER ou !!!!!$$USER ou $'USER'
			}
		}
	}
	return (0);
}