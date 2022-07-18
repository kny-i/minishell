#include "utils.h"

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
	t_envp *tmp_env;


	while (tmp->next != NULL)
	{
		if (ft_strcmp(tmp->next->env_name, args[i]) == 0)
		{
			if (tmp->next->next != NULL)
				tmp->next = tmp->next->next;
			else
			{
				tmp_env = tmp->next;
				tmp->next = NULL;
				free_env(tmp_env);
				break ;
			}
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
