/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:51:17 by svalente          #+#    #+#             */
/*   Updated: 2023/09/26 16:58:50 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

int     valid_quotes(char *str);
int		checker(char *rl);
char    *modify_str(char *rl);
char	**separate_args(char *rl);

#endif