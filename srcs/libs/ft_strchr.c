#include "minishell.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0' && *s != (unsigned char)c)
		s++;
	if (*s == (unsigned char)c)
		return ((char *)s);
	return (0);
}