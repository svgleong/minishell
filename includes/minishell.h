#ifndef MINISHELL_H
#define MINISHELL_H

//changed to ""

# include <alloc.h>
# include <cmd.h>
# include <string.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>

t_cmd *new_node( char *arg);

#endif