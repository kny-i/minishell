#include "utils.h"

/*
void	free_env(t_envp *envp)
{
	free(envp->env_name);
	envp->env_name = NULL;
	free(envp->content);
	envp->content = NULL;
	free(envp);
	envp = NULL;
}

void	unset_utils(t_envp *tmp, char **args, int i)
{
	t_envp	*tmp_env;

	while (tmp->next != NULL)
	{
		if (ft_strcmp(tmp->next->env_name, args[i]) == 0)
		{
			if (tmp->next->next != NULL)
			{
				tmp_env = tmp->next;
				tmp->next = tmp->next->next;
				free_env(tmp_env);
			}
			else
			{
				tmp_env = tmp->next;
				tmp->next = NULL;
				free_env(tmp_env);
			}
			break;
		}
		tmp = tmp->next;
	}
}

int	unset_core(char **args, t_envp **envp)
{
	int		i;
	t_envp	*tmp;

	i = 1;
	tmp = *envp;
	while (args[i] != NULL)
	{
		if (ft_strcmp(tmp->env_name, args[i]) == 0)
		{
			*envp = (*envp)->next;
			i++;
			continue ;
		}
		unset_utils(tmp, args, i);
		tmp = *envp;
		i++;
	}
	return (0);
}
*/
void	ft_lst_env_delone(t_envp *env, void (*del)(void *))
{
	if (env || del)
	{
		del(env->content);
		free(env);
	}
}

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