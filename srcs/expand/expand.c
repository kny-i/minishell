#include "minishell.h"

char	*expand_general(char *content, int *i, \
				char *new_content, t_envp *env_list)
{
	int		status;
	char	*tmp;

	status = get_status(*content);
	if (!ft_strncmp(content, "$", 1))
		tmp = get_expand_str(content, i, env_list);
	else
		tmp = ft_substr(content, 0, 1);
	new_content = for_free(ft_strjoin(new_content, tmp), tmp);
	return (new_content);
}

char	*launch_expand(char *content, t_envp *env_list)
{
	char	*res;
	int		status;
	int		i;

	res = NULL;
	i = 0;
	while (content[i])
	{
		status = get_status(content[i]);
		if (status == STATE_IN_QUOTE)
			res = expand_qoute(content, &i, res);
		else if (status == STATE_IN_DQUOTE)
			res = expand_dqoute(content, &i, res, env_list);
		else
			res = for_free(expand_general(content + i, &i, res, env_list), res);
		i++;
	}
	return (res);
}

void	expand_args(t_cmd *cmd_list, t_envp *env_list)
{
	t_cmd	*cur_cmd_list;
	t_list	*cur_list;

	cur_cmd_list = cmd_list;
	while (cur_cmd_list)
	{
		cur_list = cur_cmd_list->args;
		while (cur_list != NULL && cur_list->content != NULL)
		{
			cur_list->content = for_free \
			(launch_expand(cur_list->content, env_list), cur_list->content);
			cur_list = cur_list->next;
		}
		cur_cmd_list = cur_cmd_list->next;
	}
}

bool	expand(t_cmd *cmd_list, t_envp *env_list)
{
	expand_args(cmd_list, env_list);
	expand_redirect(cmd_list, env_list);
	if (open_redirect(cmd_list) == false)
		return (false);
	return (true);
}
