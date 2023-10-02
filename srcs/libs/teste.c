#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*p;

	p = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		p[i] = c;
		i++;
	}
	return (p);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, '\0', (count * size));
	return (ptr);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0' && *s != (unsigned char)c)
		s++;
	if (*s == (unsigned char)c)
		return ((char *)s);
	return (0);
}
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	if (len >= ft_strlen(s))
		len = ft_strlen(s) - start;
	if (start >= ft_strlen(s))
		return (ft_calloc(1, 1));
	sub = ft_calloc(sizeof(char), len + 1);
	if (!sub)
		return (NULL);
	while (start < ft_strlen(s) && i < len)
		sub[i++] = s[start++];
	return (sub);
}

static size_t	ft_countword(char const *s, char c)
{
	size_t	count;

	if (!*s)
		return (0);
	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s != c && *s)
			s++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**lst;
	size_t	word_len;
	int		i;

	if (!s)
		return (0);
	lst = (char **)malloc((ft_countword(s, c) + 1) * sizeof(char *));
	if (!lst)
		return (0);
	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s == '\0')
			break ;
		if (!ft_strchr(s, c))
			word_len = ft_strlen(s);
		else
			word_len = ft_strchr(s, c) - s;
		lst[i++] = ft_substr(s, 0, word_len);
		s += word_len;
	}
	lst[i] = NULL;
	return (lst);
}

int main()
{
    char *s = "afasfa22|22fasfa2fa2|2fasa";
    char c = '2';
    char **lst = ft_split(s, c);
    int i = 0;
    while (lst[i])
    {
        printf("%s\n", lst[i]);
        i++;
    }
    return (0);
}