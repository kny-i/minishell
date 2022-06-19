#include "env.h"

char *get_env(char *name, t_envp *en_list)
{
	char *ret;

	while (en_list != NULL)
	{
		if (strcmp(name, en_list->env_name) == 0)
			return (en_list->content);
		en_list = en_list->next;
	}
	return (NULL);

}

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

t_envp *creat_tenv(void)
{
	t_envp *env_tmp;
	t_envp *env_list;
	int i;
	int k;
	int j;
	extern char **environ;

	i = 0;
	env_tmp = ft_envnew(0);
	env_list = env_tmp;
	while(environ[i] != NULL)
	{
		k = 0;
		while (environ[i][k] != '=')
			k++;
		env_tmp->env_name = ft_substr(environ[i], 0, k);
		j = 0;
		while (environ[i][j] != '\0')
			j++;
		env_tmp->content = ft_substr(environ[i], k + 1, j);
		env_tmp->next = ft_envnew(0);
		env_tmp = env_tmp->next;
		i++;
	}
	return (env_list);
}