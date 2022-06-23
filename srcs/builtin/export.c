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

void print_env_expo(t_envp *envp)
{
	while (envp!= NULL)
	{
		ft_putstr_fd("export ", 1);
		ft_putstr_fd(envp->env_name, 1);
		ft_putchar_fd('=', 1);
		ft_putchar_fd('"', 1);
		ft_putstr_fd(envp->content, 1);
		ft_putchar_fd('"', 1);
		ft_putchar_fd('\n', 1);
		envp= envp->next;
	}
}

bool is_env(char *env_name, t_envp *envp)
{
	while(envp != NULL)
	{
		if (ft_strcmp(env_name, envp->env_name) == 0)
			return (true);
		envp = envp->next;
	}
	return (false);
}

void env_content_change(char *env_name, char *content, t_envp **envp)
{
	t_envp *tmp;

	tmp = *envp;
	while (tmp != NULL)
	{
		if (ft_strcmp(env_name, tmp->env_name) == 0)
			tmp->content = content;
		tmp = tmp->next;
	}
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
		print_env_expo(*env);
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
			if (is_env(env_name, *env) == 1)
				env_content_change(env_name, content, env);
			else
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