/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 13:02:23 by svalente          #+#    #+#             */
/*   Updated: 2023/10/03 17:38:57 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
				expansion(cmds->args[i][j]);
		}
	}
	return (0);
}

int	expansion(char *str)
{
	int	i;

	i = 0;
	while (str[++i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			//apagar $ e numero
		//se nao existe apagar ate $
		//se existir copiar a partir do igual
		//se encontrar ' depois de $ nao expande echo "$'PATH'" --> $'PATH'
	}
}