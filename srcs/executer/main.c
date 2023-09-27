#include "./includes/executer.h"

void cd_command() {
    printf("Running 'cd' command.\n");
}

void pwd_command() {
    printf("Running 'pwd' command.\n");
}

void echo_command() {
    printf("Running 'echo' command.\n");
}

t_env	*env(void)
{
	static t_env env;
	return (&env);
}

void	print_env(t_env *env)
{
	t_env *tmp = env;

	if(!env)
	{
		printf("Empty list\n");	
		return ;
	}
	while (tmp)
	{
		printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
}

int main(int ac, char **av, char **env)
{
    (void)ac;
	(void)av;
	t_env *env_list = get_env_to_list(env);
	print_env(env_list);
	return (0);
}