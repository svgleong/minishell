//echo [-n][args]
// prints in the terminal what we ask
// echo $(pwd)
//echo -n needs to be first arg
// echo -n "hello" -> hello
// echo ... -n -> ... -n\n
// echo -n ... -> ... $bash_prompt
// in defautl > writes to stdin, if file exists, overwrites it
// prepare actions for echo remapping fds

#include <executer.h>

int	check_n(char *s)
{
	int i = 0;

	if (!(s[0] == '-'))
		return(-1);
	while (s[++i])
	{
		if (s[i] != 'n')
			return (1);
	}
	return (0);
}

void    echo(t_cmd *cmd)
{
	bool	new_line;
	int		i;

	i = 1;
	new_line = true;
    if (cmd->args[1] && !check_n(cmd->args[1]) && i++)
		new_line = false;
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i++]);
		if ((cmd->args[i] != NULL))
			printf(" ");
	}
	if (new_line == true)
		printf("\n");
}
