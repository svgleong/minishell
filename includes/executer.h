#ifndef EXECUTER_H
# define EXECUTER_H

# include "builtin.h"
# include <minishell.h>


# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>

typedef struct s_cmdd
{
	char			**args;
}	t_cmdd;



//utils
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s);

//env-bi
void    env_bi(char **env,t_env *env_lst);
t_env	*env(void);
t_export_env	*export_env(void);
void	get_env_to_list(char **env);
void	print_env();


//cmd
void    echo_bi(t_cmdd *cmd);
//pwd
void    pwd_bi(void);

void	only_export();



#endif

