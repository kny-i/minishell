#include "minishell.h"

void	create_tenv_utils(char **envp, t_envp *env_tmp)
{
	int	i;
	int	k;
	int	j;

	i = 0;
	while (envp[i] != NULL)
	{
		k = 0;
		while (envp[i][k] != '=')
			k++;
		env_tmp->env_name = ft_substr(envp[i], 0, k);
		j = 0;
		while (envp[i][j] != '\0')
			j++;
		env_tmp->content = ft_substr(envp[i], k + 1, j);
		if (envp[i + 1] == NULL)
			break ;
		env_tmp->next = ft_envnew(NULL, NULL);
		env_tmp = env_tmp->next;
		i++;
	}
}
