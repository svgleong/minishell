#include <minishell.h>

char	*ft_strdup(const char *s)
{
	char	*dest;
	int		leng_s;
	int		i;

	leng_s = ft_strlen((const char *)s);
	dest = ft_calloc(leng_s + 1, sizeof(char)); //(char *)malloc(sizeof(char) * (leng_s +1));
	if (!dest)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return ((char *)dest);
}
char	*ft_strdup_special(const char *s, int c)
{
	char	*dest;
	int		leng_s;
	int		i;

	if (s[0] == c)
		return NULL;
	leng_s = ft_strlen_special((const char *)s, c);
	dest = ft_calloc(leng_s + 1, sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return ((char *)dest);
}