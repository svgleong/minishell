/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:44:41 by svalente          #+#    #+#             */
/*   Updated: 2023/11/08 16:44:54 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	ft_clean_buff(char *str)
{
	size_t	i;
	size_t	j;
	bool	newline;

	i = 0;
	j = 0;
	newline = false;
	while (str[i])
	{
		if (newline == true)
			str[j++] = str[i];
		if (str[i] == '\n')
			newline = true;
		str[i++] = '\0';
	}
	return (newline);
}

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1];
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	while (buff[0] != '\0' || read(fd, buff, BUFFER_SIZE) > 0)
	{
		line = ft_strjoin(line, buff);
		if (ft_clean_buff(buff) == true)
			break ;
		if (read(fd, buff, 0) < 0)
		{
			free(line);
			return (NULL);
		}
	}
	return (line);
}
