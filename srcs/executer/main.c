#include <executer.h>

/* void cd_command() {
    printf("Running 'cd' command.\n");
}

void pwd_command() {
    printf("Running 'pwd' command.\n");
}

void echo_command() {
    printf("Running 'echo' command.\n");
} */

/* t_env	*env(void)
{
	static t_env env;
	return (&env);
} */

void	_init(t_cmd)
{
	
}

int main(int ac, char **av, char **env)
{
    (void)ac;
	(void)av;
	t_cmd cmd;
	
	t_env *env_list;
    env_list = NULL;
	env_bi(env, env_list);
	return (0);
}