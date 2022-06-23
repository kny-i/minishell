#include "builtin.h"
#include "env.h"
#include "utils.h"


int	export_core(char **args, t_envp **env)
{
	char **tmp;
	char *line;
	char *env_name;
	char *content;
	int	 i;
	int  cnt_env;


	tmp = args;
	i = 1; //skip the first str which is expor
	cnt_env = 0;
	if (tmp[i] == NULL)
		env_core(*env);
	while (tmp[i] != NULL)
	{
		line = x_strdup(tmp[i]);
		if (strcmp(line, "=") != 0 || line[0] == '=')
			continue;
		env_name = ft_strchr(line, '=');
		while(*line != '=')
			line++;
		content = ft_memmove(content, line, ft_strlen(line));
		if (env_name != NULL)
			env_add_back(env_name, content, env);





		i++;
	}
	return (0);
}