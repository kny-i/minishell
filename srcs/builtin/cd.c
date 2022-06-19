#include "minishell.h"
#include <unistd.h>
#include "env.h"


void cd_home(t_envp *envp)
{
	char *home_path;

	home_path = get_env("HOME", envp);
	if (home_path == NULL)
	{
		perror("HOME doesn't exist");
		exit(1);
	}
	if (chdir(home_path) == -1)
	{
		perror("chdir error");
		exit(1);
	}
}

int cd_core(t_cmd *cmd, t_envp *env)
{
	char	**args;
	char	**env_array;
	int 	status;

	args = list_to_args(cmd);
	env_array = list_to_env(env);
	if (cmd->args == NULL)
	{
		cd_home(env);
	}
	if (chdir(args[1]) == -1)
	{
		perror("chdir error");
		exit(1);
	}
	return (0);
}