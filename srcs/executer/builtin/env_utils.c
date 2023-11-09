#include <minishell.h>

void	simple_env(void)
{
	char	**env;
	char	*pwd = getcwd(NULL, 0);
	char	*temp;
	env = malloc(sizeof(char *) * 4);
	env[0] = ft_strdup("SHLVL=0");
	temp = ft_strjoin_free("PWD=", pwd, -1);
	env[1] = ft_strdup(temp);
	env[2] = ft_strdup("OLDPWD");
	env[3] = NULL;
	free(pwd);
	free(temp);
	get_env_to_list(env);
	free_matrix(env);
}

void	env_checker(char **env)
{
	if (env)
		if (!data()->envp)
			get_env_to_list(env);
	if (!env[0])
		simple_env();
}