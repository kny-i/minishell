#include "builtin.h"
#include "env.h"
#include "utils.h"

void 	env_add_back(t_envp **envp, t_envp *new)
{
	t_envp *tmp;

	tmp = *envp;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}
bool has_char(const char *str, char c)
{
	int i;

	i = 0;
	while(str[i] != '\0')
	{
		if (str[i] == c)
			return (true);
		i++;
	}
	return (false);
}
char *strcpy_untill_c(char *dst,const char *src, char c)
{
	int i;
	int k;

	i = 0;
	k = 0;
	while(src[i] != c)
		i++;
	dst = (char *) x_calloc(sizeof (char), i);
	while(src[k] != c)
	{
		dst[k] = src[k];
		k++;
	}
	return (dst);
}

int	export_core(char **args, t_envp **env)
{
	char **tmp;
	char *line;
	char *env_name;
	char *content;
	int	 i;

	tmp = args;
	i = 1; //skip the first str which is expor
	if (tmp[i] == NULL)
		env_core(*env);
	while (tmp[i] != NULL)
	{
		line = x_strdup(tmp[i]);
		if (has_char(line, '=') == 0 || line[0] == '=')
		{
			i++;
			free(line);
			continue;
		}
		env_name = strcpy_untill_c(env_name, line, '=');
		while(*line != '=')
			line++;
		line++;//skip '='
		content = line;
		if (env_name != NULL)
		{
			env_add_back(env, ft_envnew(env_name,content));
			i++;
			//free(line);
			continue;
		}
		free(line);
		i++;
	}
	return (0);
}