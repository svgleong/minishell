/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzarichn <mzarichn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 13:02:23 by svalente          #+#    #+#             */
/*   Updated: 2023/10/06 12:06:39 by mzarichn         ###   ########.fr       */
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
	return (ft_strlen_special(str, '$') + ft_strlen(value) + \
	ft_strlen(ft_strchr(str, '$') + key));
}

char	*expanding(char *str , char *value, int key) 
{
	char	*result;
	int		sz;
	int		i;
	int		j;
	int		k;

	sz = calculate_result(str, value, key);
	//printf("sz: %d\n", sz);
	result = malloc(sz);
	i = -1;
	j = -1;
	while (str[++i] != '$')
		result[i] = str[i];
	k = i  + key + 1;
	while (value[++j])
		result[i++] = value[j];
	while (str[k])
		result[i++] = str[k++];
	result[i] = '\0';
	printf("result %s\n", result);
	return (result);	
}

char	*expansion(char *str, int i)
{
	t_env	*env;

	env = data()->envp;
	char *value = NULL;
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
	// remove_expand();

	// while (str[++i])
	// {
	// 	if (!ft_isalpha(str[i]) || str[i] != '_')
			
	// 	//apagar $ e numero
	// 	//se nao existe apagar ate $
	// 	//se existir copiar a partir do igual
	// 	//se encontrar ' depois de $ nao expande echo "$'PATH'" --> $'PATH'
	// }
	return (str);
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
				free(cmds->args[i]);
				cmds->args[i] = tmp;
				j = -1;
				//(void)tmp;
				// $+USER ou $$USER ou $'USER'
			}
		}
	}
	return (0);
}