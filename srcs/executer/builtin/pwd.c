#include <executer.h>

void    pwd_bi(t_cmd *cmd)
{
    char	*buf;
	(void)cmd;
	buf = getcwd(NULL, 0);
	ft_putendl_fd(buf, 1);
	free(buf);
	return ;
}