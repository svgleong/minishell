#include <minishell.h>

char    *ft_strjoin(char *s1, char *s2)
{
    char    *new;
    int     i;
    int     j;

    i = 0;
    j = 0;
    new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
    if (new == NULL)
        return (NULL);
    while (s1[i])
    {
        new[i] = s1[i];
        i++;
    }
    while (s2[j])
    {
        new[i + j] = s2[j];
        j++;
    }
    new[i + j] = '\0';
    return (new);
}