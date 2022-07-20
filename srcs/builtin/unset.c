#include "utils.h"

void	free_env(t_envp *env)
{
	t_envp	*envp;

	envp = env;
	if (env != NULL)
	{
		free(envp->env_name);
		envp->env_name = NULL;
		free(envp->content);
		envp->content = NULL;
		free(envp);
		envp = NULL;
	}
}

void	remove_env(t_envp **envp, t_envp *remove_env)
{
	t_envp	*tmp;

	if (*envp == NULL || remove_env == NULL)
		return ;
	if (*envp == remove_env)
		*envp = (*envp)->next;
	else
	{
		tmp = (*envp);
		while (tmp != NULL && tmp->next != NULL)
		{
			if (tmp->next == remove_env)
			{
				tmp->next = remove_env->next;
				break ;
			}
			tmp = tmp->next;
		}
		free_env(remove_env);
	}
}

void	unset_utils(t_envp **env, char *key)
{
	t_envp	*tmp;

	tmp = *env;
	while (tmp != NULL)
	{
		if (ft_strcmp(key, tmp->env_name) == 0)
		{
			remove_env(env, tmp);
			return ;
		}
		tmp = tmp->next;
	}
}

int	unset_core(char **args, t_envp **envp)
{
	int	i;

	i = 1;
	while (args[i] != NULL)
	{
		unset_utils(envp, args[i]);
		i++;
	}
	return (0);
}
