
#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

char	*find_env_path(t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, "PATH") == 0)
			return (env->content);
		env = env->next;
	}
	return (NULL);
}

char	*ft_strtok(char *str, const char *delim)
{
	static char	*last_str = NULL;
	static char	last_char = '\0';
	char		*token;

	if (str == NULL && last_str == NULL)
		return (NULL);
	if (str != NULL)
		last_str = str;
	token = last_str;
	while (*last_str)
	{
		if (*last_str == *delim)
		{
			last_str++;
			delim++;
			if (*delim == '\0')
			{
				last_str++;
				break ;
			}
			last_char = *delim;
		}
		else
		{
			last_char = *last_str;
			last_str++;
		}
	}
	if (last_char == '\0')
		last_str = NULL;
	else
		*last_str++ = '\0';
	return (token);
}

void *ft_memcpy(void *dest, const void *src, size_t n)
{
	char *csrc = (char *)src;
	char *cdest = (char *)dest;
	for (size_t i = 0; i < n; i++)
		cdest[i] = csrc[i];
	return dest;
}

char	*ft_strjoin_free(char *s1, char *s2, int free_str)
{
	char	*new_str;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new_str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, s1, s1_len);
	ft_memcpy(new_str + s1_len, s2, s2_len);
	new_str[s1_len + s2_len] = '\0';
	if (free_str == 1 || free_str == 3)
		free(s1);
	if (free_str == 2 || free_str == 3)
		free(s2);
	return (new_str);
}

int	can_execute_command(char *command, t_env *env)
{
	char	*path = find_env_path(env);
	char	*path_copy = path ? ft_strdup(path) : NULL;
	char	*path_token = path_copy ? ft_strtok(path_copy, ":") : NULL;
	int		can_execute = 0;

	while (path_token)
	{
		char	*full_path = ft_strjoin_free(path_token, "/", -1);
		full_path = ft_strjoin_free(full_path, command, 1);
		if (access(full_path, X_OK) == 0)
		{
			printf("can execute\n");
			can_execute = 1;
			break ;
		}
		free(full_path);
		path_token = ft_strtok(NULL, ":");
	}
	free(path_copy);
	return (can_execute);
}


 