#ifndef BUILTIN_H
# define BUILTIN_H

//enum -> struct but each line of definition has a number
typedef enum s_token
{
	GREAT = 1,
	GREAT_GREAT,
	LESS,
	LESS_LESS,
}	t_token;

//string to know if theres a token or not
typedef struct s_lexer
{
	char			*str;
	t_token			token;
}	t_lexer;

//command struct
//ex: ls-la > output.txt < input.txt
/* typedef struct s_cmd
{
	char			**cmd;
	int				n_redr;
	t_lexer			*redr;
}	t_cmd;
 */

typedef struct s_env
{
	char			*content;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_export_env
{
	char			*content;
	struct s_env	*next;
	struct s_env	*prev;
}	t_export_env;

t_env	*envp(void);

#endif