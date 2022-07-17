#include "minishell.h"

int	get_status(char c)
{
	int	char_type;

	char_type = get_char_type(c);
	if (char_type == CHAR_QOUTE)
		return (STATE_IN_QUOTE);
	else if (char_type == CHAR_DQOUTE)
		return (STATE_IN_DQUOTE);
	else
		return (STATE_GENERAL);
}

char	*search_env(char *env_name, t_envp *env_list)
{
	t_envp	*tmp;

	tmp = env_list;
	while (tmp)
	{
		if (!ft_strncmp(env_name, tmp->env_name, ft_strlen(env_name)))
			return (ft_strdup(tmp->content));
		tmp = tmp->next;
	}
	return (ft_strdup(""));
}

char	*get_expand_str(char *content, int *i, t_envp *env_list)
{
	int		len;
	char	*res;

	len = 1;
	if (!ft_isalpha(content[len]))
		return (ft_substr(content, 0, len));
	while (ft_isalpha(content[len]) == 1)
	{
		len++;
		*i += 1;
	}
	res = ft_substr(content, 1, len - 1);
	res = for_free(search_env(res, env_list), res);
	return (res);
}

char	*expand_qoute(char *content, int *i, char *new_content)
{
	int		status;
	char	*tmp;

	*i += 1;	//最初は'だから
	status = get_status(content[*i]);
	if (status == STATE_IN_QUOTE)
		return (ft_strdup(new_content));
	while (status != STATE_IN_QUOTE)
	{
		tmp = ft_substr(content + *i, 0, 1);
		new_content = for_free(ft_strjoin(new_content, tmp), new_content);
		free(tmp);
		*i += 1;
		status = get_status(content[*i]);
	}
	return (new_content);
}

char	*expand_dqoute(char *content, int *i, char *new_content, t_envp *env_list)
{
	int		status;
	char	*tmp;

	*i += 1;	//最初は"だから
	status = get_status(content[*i]);
	if (status == STATE_IN_DQUOTE)
		return (ft_strdup(new_content));
	while (status != STATE_IN_DQUOTE)
	{
		if (!ft_strncmp(content + *i, "$", 1))
			tmp = get_expand_str(content + *i, i, env_list);
		else
			tmp = ft_substr(content + *i, 0, 1);
		new_content = for_free(ft_strjoin(new_content, tmp), new_content);
		free(tmp);
		*i += 1;
		status = get_status(content[*i]);
	}
	return (new_content);
}

char	*expand_general(char *content, int *i, char *new_content, t_envp *env_list)
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

	//res = NULL;
	i = 0;
	while (content[i])
	{
		status = get_status(content[i]);
		if (status == STATE_IN_QUOTE)
			res = for_free(expand_qoute(content, &i, res), res);
		else if (status == STATE_IN_DQUOTE)
			res = for_free(expand_dqoute(content, &i, res, env_list), res);
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
			cur_list->content = for_free(launch_expand(cur_list->content, env_list), cur_list->content);
			cur_list = cur_list->next;
		}
		cur_cmd_list = cur_cmd_list->next;
	}
}

void	expand_redirect(t_cmd *cmd_list, t_envp *env_list)
{
	t_cmd		*cur_cmd_list;
	t_redirect	*cur_redirect;

	cur_cmd_list = cmd_list;
	while (cur_cmd_list)
	{
		cur_redirect = cur_cmd_list->redirect;
		while (cur_redirect != NULL && cur_redirect->file_name != NULL)
		{
			cur_redirect->file_name = for_free(launch_expand(cur_redirect->file_name, env_list), cur_redirect->file_name);
			cur_redirect = cur_redirect->next;
		}
		cur_cmd_list = cur_cmd_list->next;
	}
}

bool	expand(t_cmd *cmd_list, t_envp *env_list)
{
	expand_args(cmd_list, env_list);
	expand_redirect(cmd_list, env_list);
//	if (open_redirect(cmd_list) == false)
//		return (false);
	return (true);
}
