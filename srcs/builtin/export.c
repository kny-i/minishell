#include "builtin.h"
#include "env.h"
#include "utils.h"

t_envp *env_new(char *env_name, char *content)
{
	t_envp *new;

	new = x_calloc(sizeof (t_envp), 1);
	new->next = NULL;
	new->content = content;
	new->env_name = env_name;
	return (new);
}

void 	env_add_back(t_envp **envp, t_envp *new)
{
	t_envp *tmp;

	tmp = *envp;
	while (tmp != NULL)
		tmp = tmp->next;
}

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
			env_add_back(env, env_new());





		i++;
	}
	return (0);
}