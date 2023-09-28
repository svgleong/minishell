#ifndef EXECUTER_H
# define EXECUTER_H

# include "builtin.h"
# include <minishell.h>


# include <string.h>
# include <stdlib.h>
# include <stdio.h>

//utils
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s);

//env-bi
void    env_bi(char **env,t_env *env_lst);
t_env	*env(void);
t_env	*get_env_to_list(char **env);


#endif

