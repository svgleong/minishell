/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 13:02:23 by svalente          #+#    #+#             */
/*   Updated: 2023/10/04 15:24:41 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_status(char *str, int i)
{
	(void)str;
	(void)i;
	return NULL;
}
char	*expansion(char *str, int i)
{
	t_env	*env;
	char	*value;

	env = data()->envp;
	value =
	printf("Argm: %s\n", str);
	if (str[i + 1] == '?')
		str = get_status(str, i);
	while (env->next)
	{
		printf("env: %s\n", env->content);
		if (!(ft_strncmp(str + i + 1, env->content, ft_strlen_special(env->content, '='))))
		{
			printf("TRUE\n");
				
		}
		else
			printf("false\n");
		env = env->next;
	}

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
	int	i;
	int	j;

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
				expansion(cmds->args[i], j);
		}
	}
	return (0);
}