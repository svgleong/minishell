#ifndef BUILTIN_H
# define BUILTIN_H
/* //enum -> struct but each line of definition has a number
typedef enum s_token
{
	GREAT = 1,
	GREAT_GREAT,
	LESS,
	LESS_LESS,
}	t_token; */

/* //string to know if theres a token or not
typedef struct s_lexer
{
	char			*str;
	t_token			token;
}	t_lexer; */

typedef struct s_env
{
	char			*content;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;


typedef struct s_data
{
	t_env			*envp;
} t_data;

t_data	*data(void);
t_env	*env(void);

void    free_env_list(t_env **lst);

#endif