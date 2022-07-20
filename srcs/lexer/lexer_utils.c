#include "minishell.h"

bool	compare_redirect(char *str)
{
	if (ft_strlen(str) == 1)
	{
		if (!ft_strcmp(str, ">") || !ft_strcmp(str, "<"))
			return (true);
	}
	return (false);
}

int	check_return_status(t_token **token, int status)
{
	if ((*token)->data != NULL)
	{
		(*token)->next = token_new();
		*token = (*token)->next;
	}
	return (status);
}

int	join_return_status(t_token **token, char *str, int char_type, int status)
{
	if (char_type == CHAR_GENERAL && compare_redirect((*token)->data))
		status = check_return_status(&(*token), status);
	(*token)->data = for_free(ft_strjoin((*token)->data, str), (*token)->data);
	return (status);
}

int	check_token_return_status(t_token **token, \
				char *input, int char_type, int status)
{
	if (char_type == CHAR_PIPE)
	{
		status = check_return_status(&(*token), status);
		status = join_return_status(&(*token), input, char_type, status);
		return (check_return_status(&(*token), status));
	}
	else if (compare_redirect((*token)->data))
	{
		status = join_return_status(&(*token), input, char_type, status);
		return (check_return_status(&(*token), status));
	}
	status = check_return_status(&(*token), status);
	return (join_return_status(&(*token), input, char_type, status));
}

int	assign_general(t_token **token, char *input, int char_type)
{
	int		status;
	char	*str;

	str = ft_substr(input, 0, 1);
	if (char_type == CHAR_QOUTE)
		status = join_return_status(&(*token), str, char_type, STATE_IN_QUOTE);
	else if (char_type == CHAR_DQOUTE)
		status = join_return_status(&(*token), str, char_type, STATE_IN_DQUOTE);
	else if (char_type == CHAR_GENERAL)
		status = join_return_status(&(*token), str, char_type, STATE_GENERAL);
	else if (char_type == CHAR_WHITESPACE)
		status = check_return_status(&(*token), STATE_GENERAL);
	else
		status = check_token_return_status(&(*token), \
												str, char_type, STATE_GENERAL);
	free(str);
	return (status);
}
