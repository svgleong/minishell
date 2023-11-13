/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 20:33:04 by svalente          #+#    #+#             */
/*   Updated: 2023/11/13 11:16:57 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	parser(char *rl)
{
    char **tmp;

    if (!checker(rl))
        return (0);
    tmp = separate_args(rl);
    if (!create_list(&data()->pointer_cmd, tmp))
    {
        cmdlstclear(&data()->pointer_cmd);
        return (0);
    }
    return (1);
}
