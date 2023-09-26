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
typedef struct s_cmd
{
	char			**cmd;
	int				n_redr;
	t_lexer			*redr;
}	t_cmd;

typedef struct s_list
{
	char			**content;
	char			*path;
	int				fd_master[2];
	int				fd[2];
	int				master_error[2];
	struct s_list	*next;
	struct s_list	*prev;
	void			(*ft_exec)(struct s_list **list);
}	t_list;



#endif