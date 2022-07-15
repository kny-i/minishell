#include "minishell.h"

int	cnt_env(t_envp *envp)
{
	int	env_cnt;

	env_cnt = 0;
	while (envp != NULL)
	{
		env_cnt++;
		envp = envp->next;
	}
	return (env_cnt);
}

char	*get_path(t_envp *envp)
{
	t_envp	*tmp;

	tmp = envp;
	while (tmp != NULL && ft_strcmp(tmp->env_name, "PATH"))
	{
		tmp = tmp->next;
	}
	return (tmp->content);
}

t_envp	*ft_envnew(char *env_name, char *content)
{
	t_envp	*envp_list;

	envp_list = x_calloc(1, sizeof(t_envp));
	envp_list->content = content;
	envp_list->next = NULL;
	envp_list->env_name = env_name;
	return (envp_list);
}

t_envp	*create_tenv(char **envp)
{
	t_envp	*env_tmp;
	t_envp	*env_list;

	env_tmp = ft_envnew(NULL, NULL);
	env_list = env_tmp;
	create_tenv_utils(envp, env_tmp);
	return (env_list);
}

char	*get_env_content(t_envp *env, char *name)
{
	while (env != NULL)
	{
		if (ft_strcmp(name, env->env_name) == 0)
			return (ft_strdup(env->content));
		env = env->next;
	}
	return (NULL);
}
