#include "env.h"


t_envp *ft_envnew(char *data)
{
	t_envp *envp_list;

	envp_list = ft_calloc(1, sizeof(t_envp));
	if (envp_list == NULL)
	{
		perror("calloc error");
		exit(1);
	}
	envp_list->content = NULL;
	envp_list->next = NULL;
	envp_list->env_name = data;
	return (envp_list);

}

t_envp *creat_tenv(char **envp)
{
	t_envp *env_tmp;
	t_envp *env_list;
	int i;
	int k;
	int j;

	i = 0;
	k = 0;
	j = 0;
	env_tmp = ft_envnew(0);
	env_list = env_tmp;
	while(envp[i] != NULL)
	{
		while (envp[i][k] != '=')
			k++;
		env_tmp->env_name = ft_substr(envp[i], 0, k);
		while (envp[i][j] != '\0')
			j++;
		env_tmp->content = ft_substr(envp[i], k + 1, j);
		env_tmp->next = ft_envnew(0);
		env_tmp = env_tmp->next;
		i++;
		k = 0;
		j = 0;
	}
	return (env_list);
}