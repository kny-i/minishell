#include "lexer.h"
#include "parser.h"
#include "utils.h"

int	get_char_type_01(char c)
{
	char	res;

	if (c == '\'')
		res = CHAR_QOUTE;
	else if (c == '\"')
		res = CHAR_DQOUTE;
	else if (c == '|')
		res = CHAR_PIPE;
	else if (c == ' ')
		res = CHAR_WHITESPACE;
	else if (c == '\t')
		res = CHAR_TAB;
	else if (c == '\n')
		res = CHAR_NEWLINE;
	else if (c == '>')
		res = CHAR_GREATER;
	else if (c == '<')
		res = CHAR_LESSER;
	else if (c == CHAR_NULL)
		res = CHAR_NULL;
	else
		res = CHAR_GENERAL;
	return (res);
}

t_token *token_new()
{
	t_token *res;

	res = ft_xmalloc(sizeof(t_token));
	res->data = NULL;
	res->next = NULL;
	res->type = -1;
	return (res);
}

int	chstatus_start(t_token *token, char *input, int status)
{
	token->data = for_free(ft_strjoin(token->data, input), token->data);
	return (status);
}

int	chstatus_end(t_token *token, char *input, int char_type, int status)
{
	token->data = for_free(ft_strjoin(token->data, input), token->data);
	if (char_type == CHAR_QOUTE)
		return (STATE_GENERAL);
	else if (char_type == CHAR_DQOUTE)
		return (STATE_GENERAL);
	return (status);
}

void	check_return_status(t_token **token)
{
	if ((*token)->data != NULL)
	{
		(*token)->next = token_new();
		*token = (*token)->next;
	}
}

void	assign_token(t_token **token, char *input)
{
	(*token)->data = for_free(ft_strjoin((*token)->data, input), (*token)->data);
	(*token)->next = token_new();
	*token = (*token)->next;
}

int	assign_general(t_token **token, char *input, int char_type)
{
	int	status = STATE_GENERAL;
	char    *str;

	str = ft_substr(input, 0, 1);
	if (char_type == CHAR_QOUTE)
		(*token)->data = for_free(ft_strjoin((*token)->data, str), (*token)->data);
	else if (char_type == CHAR_DQOUTE)
		(*token)->data = for_free(ft_strjoin((*token)->data, str), (*token)->data);
	else if (char_type == CHAR_GENERAL)
		(*token)->data = for_free(ft_strjoin((*token)->data, str), (*token)->data);
	else if (char_type == CHAR_WHITESPACE)
		check_return_status(&(*token));
	else if (char_type == CHAR_PIPE || char_type == CHAR_GREATER || char_type == CHAR_LESSER)
	{
		check_return_status(&(*token));
		assign_token(&(*token), str);
	}
	free(str);
	return (status);
}

void	lexer_build(char *input, t_lexer *lexerbuf)
{
	int 		status;
	int			char_type;
	char        *input_tmp;
	t_token 	*token;

	token = token_new();
	lexerbuf->list_token = token;
	status = STATE_GENERAL;
	input_tmp = input;
	while (*input_tmp)
	{
		char_type = get_char_type_01(*input_tmp);
		if (char_type == CHAR_PIPE)
			lexerbuf->num_token += 1;
		if (status == STATE_GENERAL)
			status = assign_general(&token, input_tmp, char_type);
		else if (status == STATE_IN_QUOTE)
			status = chstatus_end(token, input_tmp, char_type, STATE_IN_QUOTE);
		else if (status == STATE_IN_DQUOTE)
			status = chstatus_end(token, input_tmp, char_type, STATE_IN_DQUOTE);
		*input_tmp++;
	}
}
