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

/* void	cmdd_init(t_cmd *cmd)
{
	cmd->args[0] = "echo";
	cmd->args[1] = "-n";
	cmd->args[2] = "ola";
} */

void	print_args(t_cmdd *cmd)
{
	printf("Debug Args: ");
    for (int i = 0; cmd->args[i] != NULL; i++) {
        printf("%s ", cmd->args[i]);
    }
	printf("\n");
}


int main(int ac, char **av, char **env)
{
    (void)ac;
	(void)av;
	(void)env;
	t_cmdd cmd = {
		.args = (char *[]){"echo", "-nnnnnnnni", "ola", NULL}
	};
	print_args(&cmd);
	pwd_bi();

	
	t_env *env_list;
    env_list = NULL;
	//env_bi(env, env_list);

	return (0);
}