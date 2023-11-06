#include <executer.h>

void exitbuiltin(int i){
	int pid = fork();
	if (!pid){
		general_free(data()->pointer_cmd, 1, 1, 0);
		exit (i);
	}
	return ;
}

void	pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	ft_putendl_fd(buf, 1);
	free(buf);
	//data()->exit = EXIT_SUCCESS;
	exitbuiltin(EXIT_SUCCESS);
	return ;
}