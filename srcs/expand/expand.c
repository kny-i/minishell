# include "../../includes/expand.h"

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
	env_list= env_tmp;
	while(envp[i] != NULL)
	{
		while (envp[i][k] != '=')
			k++;
		env_tmp->env_name = ft_substr(envp[i], 0, k);
		printf("[%s]\n", env_tmp->env_name);
		while (envp[i][j] != '\0')
			j++;
		env_tmp->content = ft_substr(envp[i], k + 1, j);
		printf("[%s]\n", env_tmp->content);
		env_tmp->next = ft_envnew(0);
		env_tmp = env_tmp->next;
		i++;
		k = 0;
		j = 0;
	}
	return (env_list);
}


void expand_env(t_cmd *cmd, )
{
	t_cmd *cur_cmd;
	int

	cur_cmd = cmd;
	while (cur_cmd != NULL)
	{

		cur_cmd = cur_cmd->next
	}
		$PATH
}

void expand_quot(t_cmd *cmd)
{
	t_cmd *cur_cmd;
	char  *old_str;
	char  *new_str;
	char quot_type;
	int i;
	int k;

	cur_cmd = cmd;
	i = 0;
	k = 0;
	while (cur_cmd != NULL)
	{
		old_str = cur_cmd->cmd;
		while (old_str[i] != '\0')
		{
			if (old_str[i] == '\'' || old_str[i] == '\"')
			{
				quot_type = old_str[i];
				i++;
				while(old_str[i] != quot_type && )
				{

				}

			}
		}
		cur_cmd = cur_cmd->next;




	}
}
