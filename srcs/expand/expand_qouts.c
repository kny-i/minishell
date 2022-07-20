#include "minishell.h"

char	*expand_qoute(char *content, int *i, char *new_content)
{
	int		status;
	char	*tmp;

	*i += 1;
	status = get_status(content[*i]);
	if (status == STATE_IN_QUOTE)
	{
		tmp = for_free(ft_strdup(new_content), new_content);
		return (tmp);
	}
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

char	*expand_dqoute(char *content, int *i, \
								char *new_content, t_envp *env_list)
{
	int		status;
	char	*tmp;

	*i += 1;
	status = get_status(content[*i]);
	if (status == STATE_IN_DQUOTE)
	{
		tmp = for_free(ft_strdup(new_content), new_content);
		return (tmp);
	}
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
