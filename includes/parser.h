/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:51:17 by svalente          #+#    #+#             */
/*   Updated: 2023/09/27 10:59:09 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

int     valid_quotes(char *str);
int		checker(char *rl);
char    *modify_str(char *rl);
char	**separate_args(char *rl);
int		redirections(t_cmd **lst);

#endif