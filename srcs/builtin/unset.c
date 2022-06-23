#include "builtin.h"
#include "utils.h"

void free_env(t_envp *envp)
{
	free(envp->env_name);
	free(envp->content);
	free(envp);
}

int	unset_core(char **args, t_envp **envp)
{
	int i;
	t_envp *tmp;
	i = 1;
	tmp = *envp;
	while(args[i] != NULL)
	{
		if (ft_strcmp(tmp->env_name, args[i]) == 0)
		{
			*envp = (*envp)->next;
			//free_env(tmp);
			i++;
			continue;
		}
		while (tmp->next != NULL)
		{
			if (ft_strcmp(tmp->next->env_name, args[i]) == 0)
			{
				if (tmp->next->next != NULL)
					tmp->next = tmp->next->next;
				else
					tmp->next = NULL;
				//free_env(tmp->next);
				break;
			}
			tmp = tmp->next;
		}
		tmp = *envp;
		i++;
	}
	return(0);
}