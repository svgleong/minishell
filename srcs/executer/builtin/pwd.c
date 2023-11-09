#include <executer.h>

void	pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	ft_putendl_fd(buf, 1);
	free(buf);
	exitbuiltin(EXIT_SUCCESS);
	return ;
}
