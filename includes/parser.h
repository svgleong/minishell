/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:51:17 by svalente          #+#    #+#             */
/*   Updated: 2023/10/14 19:10:42 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

int     valid_quotes(char *str);
int		checker(char *rl);
char    *modify_str(char *rl);
char	**separate_args(char *rl);
int		key_value(char *str);
int		calculate_result(char *str , char *value, int key);
char	*get_status(char *str, int i);
char	*remove_expand(char *str);
char	*remove_dollar(char *str, int i);
char	*remove_character(char *str, int i);
void	expander(t_cmd **cmds);
void	remove_quotes(t_cmd **cmds);
int		redirections(t_cmd **lst);
void	check_redirections(t_cmd **cmds);
void	redirlstclear(t_redir **lst);
void	print_redir(t_redir *lst);

#endif