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

char	**list_to_env(t_envp *envp)
{
	char	**str;
	int		i;
	int		num_env;

	i = 0;
	str = NULL;
	num_env = cnt_env(envp);
	str = (char **) ft_calloc(num_env + 1, sizeof (char *));
	if (str == NULL)
	{
		perror("calloc error");
		exit(1);
	}
	while (envp != NULL)
	{
		str[i] = ft_substr(envp->env_name, 0, ft_strlen(envp->env_name) + 1);
		str[i] = for_free(ft_strjoin(str[i], "="), str[i]);
		str[i] = for_free(ft_strjoin(str[i], envp->content), str[i]);
		i++;
		envp = envp->next;
	}
	str[i] = NULL;
	return (str);
}
