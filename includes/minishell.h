#ifndef MINISHELL_H
#define MINISHELL_H

//changed to ""

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 25
# endif

# include <alloc.h>
# include <termios.h>
# include <cmd.h>
# include <string.h>
# include <string_lib.h>
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
# include <limits.h>

char	*get_next_line(int fd);
char	*find_command_path(char *command);
void	which_builtin(t_cmd *cmd);
int	    cmd_is_builtin(char *command);
int     is_valid(char *var);
char    *rem_quotes_export(char *s);
char	*check_expansion(char *str, int i);
void	update_shell_lvl(void);

// teste
void    handle_signals(void);
void	control_d(char *str);
void	sig_handler(int signal);
int	    search_expansion(t_cmd *cmds);
char	*node_value(t_env *node);
t_cmd	*get_head(t_cmd *lst);

#endif