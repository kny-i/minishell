#include "minishell.h"
#include <unistd.h>
#include "env.h"

int cd_to_home(char **args, t_envp *env)
{
	char *home_path;

	home_path = get_env_content(env, "HOME");
	if (home_path == NULL)
	{
		perror("HOME not found");
		g_signal.exit_status = 1;
		exit(1);
	}
	if (chdir(home_path) == -1)
	{
		free(home_path);
		perror("chdir error");
		exit(1);
	}
	free(home_path);
	return (0);
}

int cd_core(char **args, t_envp *env)
{
	if (args[1] == NULL)
	{
		return (cd_to_home(args, env));
	}
	if(chdir(args[1]) == -1)
	{
		perror(args[0]);
		g_signal.exit_status = 1;
		return (1);
	}
	return (0);
}