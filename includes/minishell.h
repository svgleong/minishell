#ifndef MINISHELL_H
#define MINISHELL_H

//changed to ""

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 25
# endif

# include <alloc.h>
#include <termios.h>
# include <cmd.h>
# include <string.h>
# include <parser.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>
# include <signal.h>
# include <unistd.h>
# include <builtin.h>
# include <sys/wait.h>
# include <errno.h>

char	*get_next_line(int fd);

// teste
void handle_signals(int signal);
int	search_expansion(t_cmd *cmds);

#endif