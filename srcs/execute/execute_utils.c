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
	while (tmp != NULL)
	{
		if (strcmp(tmp->content, "<") == 0 )
		{
			if (strcmp(tmp->next->content, "<") == 0)
			{
				i += 1;
				tmp = tmp->next->next->next;
				continue ;
			}
			tmp = tmp->next;
			continue ;
		}
		if (strcmp(tmp->content, ">") == 0)
			break ;
		tmp = tmp->next;
		i += 1;
	}
	return (i);
}

void	list_to_args_loop(t_list *tmp_args, int *len, char **res, t_cmd	*cmd)
{
	while (tmp_args != NULL)
	{
		if (strcmp(tmp_args->content, "<") == 0)
		{
			if (strcmp(tmp_args->next->content, "<") == 0)
			{
				res[*len] = ft_substr(cmd->heredocend, \
										0, ft_strlen(cmd->heredocend));
				len += 1;
				tmp_args = tmp_args->next->next->next;
				continue ;
			}
			tmp_args = tmp_args->next;
			continue ;
		}
		if (strcmp(tmp_args->content, ">") == 0)
			break ;
		res[*len] = ft_substr(tmp_args->content, \
										0, ft_strlen(tmp_args->content));
		tmp_args = tmp_args->next;
		*len += 1;
	}
}

char	**list_to_args(t_cmd *cmd)
{
	char	**res;
	t_list	*tmp;
	int		len;

	tmp = cmd->args;
	len = get_list_size(cmd->args);
	res = (char **)malloc(sizeof(char *) * (len + 2));
	if (res == NULL)
		exit(1);
	len = 0;
	res[len] = ft_substr(cmd->cmd, 0, ft_strlen(cmd->cmd));
	len += 1;
	list_to_args_loop(tmp, &len, res, cmd);
	res[len] = NULL;
	return (res);
}
