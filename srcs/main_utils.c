/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 21:09:12 by svalente          #+#    #+#             */
/*   Updated: 2023/11/13 21:09:13 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	init_data_var(void)
{
	data()->redir = 0;
	data()->error = 0;
}

void	init_data_var2(void)
{
	data()->exit = 0;
	data()->pointer_cmd = NULL;
}
