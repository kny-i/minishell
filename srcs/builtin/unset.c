#include "builtin.h"
#include "utils.h"


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