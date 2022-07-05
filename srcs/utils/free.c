#include "utils.h"

char	*for_free(char *res, char *free_str)
{
	if (free_str != NULL)
		free(free_str);
	free_str = NULL;
	return(res);
}

void	free_env_split(char **env_path)
{
	int	i;

	i = 0;
	while (env_path[i] != NULL)
	{
		free(env_path[i]);
		env_path[i] = NULL;
		i += 1;
	}
	free(env_path);
	env_path = NULL;
}

void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i] != NULL)
	{
		free(args[i]);
		args[i] = NULL;
		i += 1;
	}
	free(args);
}