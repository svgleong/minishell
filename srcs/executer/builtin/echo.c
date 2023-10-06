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
	if (!(s[i] == '-'))
		return(-1);
	while (s[++i])
	{
		if (s[i] != 'n')
			return (1);
	}
	return (0);

}

void    echo_bi(t_cmd *cmd)
{
	bool new_line = true;
	int i = 1;

	printf("entrou eco\n");
    if (ft_strncmp("echo", cmd->args[0], ft_strlen(cmd->args[0])))
        printf("erro not echo\n");
    if (check_n(cmd->args[1]) == 0)
	{
		new_line = false;
		printf("\nno new line\n");
		i++;
	}
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i++]);
		if (!(cmd->args[i+1] != 0))
			printf(" ");
	}
	if (new_line == true)
		printf("\n");
}
