#include "minishell.h"

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
	if (tmp->content == NULL)
		return (NULL);
	len = get_list_size(cmd->args);
	res = (char **)ft_xmalloc(sizeof(char *) * (len + 1));
	len = 0;
	list_to_args_loop(tmp, res);
	return (res);
}

bool	is_parent_exe(t_cmd *cmd_list, int cmd_cnt)
{
	if (is_builtin(cmd_list) == 1 && cmd_cnt == 1 && \
				(ft_strcmp((cmd_list)->args->content, "cd") == 0 || \
				ft_strcmp((cmd_list)->args->content, "exit") == 0 || \
				ft_strcmp((cmd_list)->args->content, "unset") == 0 || \
				ft_strcmp((cmd_list)->args->content, "export") == 0))
		return (true);
	else
		return (false);
}
