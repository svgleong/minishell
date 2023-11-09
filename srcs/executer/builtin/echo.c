// echo [-n][args]
//  prints in the terminal what we ask
//  echo $(pwd)
// echo -n needs to be first arg
//  echo -n "hello" -> hello
//  echo ... -n -> ... -n\n
//  echo -n ... -> ... $bash_prompt
//  in defautl > writes to stdin, if file exists, overwrites it
//  prepare actions for echo remapping fds

#include <executer.h>

int	check_n(char *s)
{
	int	i;

	i = 0;
	if (!(s[0] == '-'))
		return (-1);
	while (s[++i])
	{
		if (s[i] != 'n')
			return (1);
	}
	return (0);
}

/* void	echo(t_cmd *cmd)
{
	bool	new_line;
	int		i;

	i = 1;
	new_line = true;
	if (cmd->args[1] && !check_n(cmd->args[1]) && i++)
		new_line = false;
	while (cmd->args[i])
	{
		if (!check_n(cmd->args[i]))
		{
			i++;
			continue ;
		}
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1] != NULL && check_n(cmd->args[i]))
			printf(" ");
		i++;
	}
	if (new_line == true)
		printf("\n");
	exitbuiltin(EXIT_SUCCESS);
} */

int	flags(char **cmd, bool *flag)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[++i])
	{
		if (cmd[i][0] != '-')
			return (i);
		if (cmd[i][1] == '\0')
			return (i);
		j = 1;
		while (cmd[i][j])
		{
			if (cmd[i][j] != 'n')
				return (i);
			j++;
		}
		*flag = true;
	}
	return (i);
}

void	echo(t_cmd *cmd)
{
	bool flag;
	int	i;

	flag = false;
	if (!cmd->args[1])
	{
		printf("\n");
		exitbuiltin(EXIT_SUCCESS);
		return ;
	}
	i = flags(cmd->args, &flag) - 1;
	while (cmd->args[++i])
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
	}
	if (!flag)
		printf("\n");
	exitbuiltin(EXIT_SUCCESS);
}
