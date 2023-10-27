#include <executer.h>

void    pwd()
{
    char	*buf;
	buf = getcwd(NULL, 0);
	ft_putendl_fd(buf, 1);
	free(buf);
	data()->exit = EXIT_SUCCESS;
	return ;
}