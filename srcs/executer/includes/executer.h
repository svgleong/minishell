#ifndef EXECUTER_H
# define EXECUTER_H

# include "builtin.h"

# include <string.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>

t_env	*env(void);

void	*ft_calloc(size_t count, size_t size);

#endif

