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

t_env	*env(void)
{
	static t_env env;
	return (&env);
}

t_export_env	*export_env(void)
{
	static t_export_env export_env;
	return (&export_env);
}

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


/* void	list_bubble_sort(t_env *env)
{
	int swapped = 1;
	t_env *temp;
	if (!env)
		return ;
	while (swapped)
	{
		swapped = 0;
		temp = env;

		while (temp->next)
		{
			if (temp->content > temp->next->content)
			{
				char *temp2 = temp->content;
				temp->content = temp->next->content;
				temp->next->content = temp2;
				swapped = 1;
			}
			temp = temp->next;
		}
	}
	env = temp;
} */

int main(int ac, char **av, char **env)
{
    (void)ac;
	(void)av;
	t_cmdd cmd = {
		.args = (char *[]){"echo", "-nnnnnnnni", "ola", NULL}
	};
	print_args(&cmd);
	//pwd_bi();

	
	t_env *env_list;
    env_list = NULL;
	env_bi(env, env_list);
	//list_bubble_sort(env);


	return (0);
}