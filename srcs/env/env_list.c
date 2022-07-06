#include "env.h"
#include "utils.h"


int	cnt_env(t_envp *envp)
{
	int	env_cnt;

	env_cnt = 0;
	while (envp != NULL)
	{
		env_cnt++;
		envp = envp->next;
	}
	return (env_cnt);
}

char	*get_path(t_envp *envp)
{
	t_envp	*tmp;

	tmp = envp;
	while (ft_strcmp(tmp->env_name, "PATH"))
	{
		tmp = tmp->next;
	}
	return (tmp->content);
}

t_envp *ft_envnew(char *env_name, char *content)
{
	t_envp *envp_list;

	envp_list = ft_calloc(1, sizeof(t_envp));
	if (envp_list == NULL)
	{
		perror("calloc error");
		exit(1);
	}
	envp_list->content = content;
	envp_list->next = NULL;
	envp_list->env_name = env_name;
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
	env_tmp = ft_envnew(NULL, NULL);
	env_list = env_tmp;
	while(envp[i] != NULL)
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
			break;
		env_tmp->next = ft_envnew(NULL, NULL);
		env_tmp = env_tmp->next;
		i++;
	}
	return (env_list);
}

char *get_env_content(t_envp *env, char *name)
{
	while (env != NULL)
	{
		if (ft_strcmp(name, env->env_name) == 0)
			return (ft_strdup(env->content));
		env = env->next;
	}
	return (NULL);
}