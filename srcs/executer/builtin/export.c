/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:41:17 by svalente          #+#    #+#             */
/*   Updated: 2023/11/13 21:06:38 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_env	*search_env(char *var)
{
	t_env	*envp;

	envp = data()->envp;
	while (envp && envp->content != NULL)
	{
		if (!ft_strncmp(envp->content, var, \
			ft_strlen_special(envp->content, '=')))
			return (envp);
		envp = envp->next;
	}
	return (NULL);
}

void	update_env_export(char *cmd, char **new_var)
{
	t_env	*node;
	char	*var;
	char	*value;

	var = new_var[0];
	value = new_var[1];
	if (!value)
		value = "";
	node = search_env(var);
	if (node == NULL)
		env_add_node_end(data()->envp, env_new_node(cmd));
	if (node && value)
	{
		free(node->content);
		node->content = ft_strdup(cmd);
	}
}

int	verify_export_arg(char *arg)
{
	if (is_valid(arg) == 0)
	{
		ft_putstr_fd("not a valid identifier\n", STDERR_FILENO);
		return (0);
	}
	return (1);
}

void	normal_export(t_cmd *cmd, int i)
{
	char	**var_value;

	while (cmd->args[++i])
	{
		if (!verify_export_arg(cmd->args[i]))
			continue ;
		var_value = ft_split(cmd->args[i], '=');
		update_env_export(cmd->args[i], var_value);
		free_matrix(var_value);
	}
}

void	export(t_cmd *cmd)
{
	int		i;
	char	**export_env;

	i = 0;
	export_env = NULL;
	if (!(cmd->args[1]))
	{
		export_env = env_to_matrix();
		bubble_sort(export_env);
		print_export(export_env);
		free_matrix(export_env);
		data()->exit = EXIT_SUCCESS;
		return ;
	}
	else
		normal_export(cmd, i);
}
