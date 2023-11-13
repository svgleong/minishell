/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:41:17 by svalente          #+#    #+#             */
/*   Updated: 2023/11/13 12:31:08 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	get_env_to_list(char **env)
{
	int	i;

	i = 0;
	if (!env[0])
		return ;
	data()->redir = 0;
	data()->envp = env_new_node(env[0]);
	while (env[++i])
		env_add_node_end(data()->envp, env_new_node(env[i]));
	update_shell_lvl();
}

void	simple_env(void)
{
	char	**env;
	char	*pwd;
	char	*temp;

	pwd = getcwd(NULL, 0);
	env = malloc(sizeof(char *) * 4);
	env[0] = ft_strdup("SHLVL=0");
	temp = ft_strjoin_free("PWD=", pwd, -1);
	env[1] = ft_strdup(temp);
	env[2] = ft_strdup("OLDPWD");
	env[3] = NULL;
	free(pwd);
	free(temp);
	get_env_to_list(env);
	free_matrix(env);
}

void	env_checker(char **env)
{
	if (env)
		if (!data()->envp)
			get_env_to_list(env);
	if (!env[0])
		simple_env();
}

int	list_size_env(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**env_to_matrix(void)
{
	int		len;
	char	**matrix;
	t_env	*temp;

	temp = (t_env *)data()->envp;
	len = list_size_env(temp);
	matrix = malloc(sizeof(char *) * (len + 1));
	if (!matrix)
		return (NULL);
	temp = (t_env *)data()->envp;
	len = 0;
	while (temp)
	{
		matrix[len] = ft_strdup(temp->content);
		if (!matrix[len])
			return (NULL);
		temp = temp->next;
		len++;
	}
	matrix[len] = NULL;
	return (matrix);
}
