#include <minishell.h>

void	init_data_var(void)
{
	data()->redir = 0;
	data()->error = 0;
}

void	init_data_var2(void)
{
	data()->exit = 0;
	data()->pointer_cmd = NULL;
}
