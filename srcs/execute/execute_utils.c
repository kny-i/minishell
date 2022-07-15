#include "execute.h"
#include "utils.h"
#include "env.h"

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

int	count_cmd(t_cmd *cmd)
{
	int	cmd_cnt;

	cmd_cnt = 0;
	while (cmd != NULL)
	{
		cmd_cnt++;
		cmd = cmd->next;
	}
	return (cmd_cnt);
}

int	get_list_size(t_list *args)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = args;
	while (tmp != NULL && tmp->content != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

void	list_to_args_loop(t_list *args_list, char **execve_args)
{
	int	i;

	i = 0;
	while (args_list != NULL && args_list->content != NULL)
	{
		execve_args[i] = ft_strdup(args_list->content);
		args_list = args_list->next;
		i++;
	}
	execve_args[i] = NULL;
}

char	**list_to_args(t_cmd *cmd)
{
	char	**res;
	t_list	*tmp;
	int		len;

	tmp = cmd->args;
	len = get_list_size(cmd->args);
	res = (char **)ft_xmalloc(sizeof(char *) * (len + 1));
	len = 0;
	list_to_args_loop(tmp, res);
	return (res);
}
