#include "builtin.h"
#include "env.h"
#include "utils.h"

void	env_content_change(char *env_name, char *content, t_envp **envp)
{
	t_envp	*tmp;
	char 	*tmp_str;
	tmp = *envp;
	while (tmp != NULL)
	{
		if (ft_strcmp(env_name, tmp->env_name) == 0)
		{
			tmp_str = tmp->content;
			tmp->content = content;
			free(tmp_str);
		}
		tmp = tmp->next;
	}
}
int	export_core(char **args, t_envp **env)
{
	char	**tmp;
	char	*line;
	char	*env_name;
	char	*content;
	int		i;
	int		k;

	tmp = args;
	i = 1;
	k = 0;
	if (tmp[i] == NULL)
	{
		print_env_expo(*env);
		return (0);
	}
	if ((ft_isalpha(tmp[1][0]) == 0) && tmp[1][0] != '_')
	{
		printf("'%s': not a valid identifier\n", tmp[1]);
		return (1);
	}
	while (tmp[i] != NULL)
	{
		line = x_strdup(tmp[i]);
		if (has_char(line, '=') == 0 || line[0] == '=')
		{
			i++;
			free(line);
			continue ;
		}
		env_name = strcpy_untill_c(env_name, line, '=');
		while (line[k] != '=')
			k++;
		k++;
		content = ft_substr(line, k + 1, ft_strlen(line) - k);
		free(line);
		if (env_name != NULL)
		{
			if (is_env(env_name, *env) == 1)
			{
				env_content_change(env_name, content, env);
				free(env_name);
			}
			else
				env_add_back(env, ft_envnew(env_name, content));
			i++;
			env_name = NULL;
			continue ;
		}
		i++;
	}
	return (0);
}
