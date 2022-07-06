#include "builtin.h"
#include "utils.h"

void	free_env(t_envp *envp)
{
	free(envp->env_name);
	free(envp->content);
	free(envp);
}

void	unset_utils(t_envp *tmp, char **args, int i)
{
	while (tmp->next != NULL)
	{
		if (ft_strcmp(tmp->next->env_name, args[i]) == 0)
		{
			if (tmp->next->next != NULL)
				tmp->next = tmp->next->next;
			else
				tmp->next = NULL;
			break ;
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
