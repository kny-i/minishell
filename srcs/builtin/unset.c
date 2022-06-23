#include "builtin.h"
#include "utils.h"

void	ft_envlst_delone(t_envp *envp, void (*del)(void *))
{
	if (envp != NULL || del != NULL)
	{
		del(envp->content);
		del(envp->env_name);
		free(envp);
	}
}

int	unset_core(char **args, t_envp **envp)
{
	int i;
	t_envp *tmp;

	i = 1;
	tmp = *envp;
	while(args[i] != NULL)
	{
		while (tmp != NULL)
		{
			if (ft_strcmp(tmp->env_name, args[i]) == 0)
			{

				continue;
			}
			tmp = tmp->next;
		}
		i++;
	}
	return(0);
}