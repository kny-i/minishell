#include "builtin.h"
#include "env.h"
#include "utils.h"

int	export_core(char **args, t_envp **env)
{
	char **tmp;
	char *line;
	int	 i;


	tmp = args;
	i = 1; //skip the first str which is export
	while (tmp[i] != NULL)
	{
		line = x_strdup(tmp[i]);

		i++;
	}
	return (0);
}