//#include "minishell.h"
#include "lexer.h"
#include "parser.h"

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

t_token	*token_init_01(t_cmd_len **len)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (new == NULL)
		exit(1);
	new->data = malloc(sizeof(char) * ((*len)->len + 1)); //おかし
	if (new->data == NULL)
		exit(1);
	ft_bzero(new->data, (*len)->len);
	new->next = NULL;
	if ((*len)->next != NULL)
		*len = (*len)->next;
	return (new);
}

int	chstatus_start(t_token *token, int *i_token, char input, int status)
{
	token->data[*i_token] = input;
	*i_token += 1;
	return (status);
}

int	chstatus_end(t_token *token, int *i_token, char input, int char_type, int status)
{
	token->data[*i_token] = input;
	*i_token += 1;
	if (char_type == CHAR_QOUTE)
		return (STATE_GENERAL);
	else if (char_type == CHAR_DQOUTE)
		return (STATE_GENERAL);
	return (status);
}

void	check_return_status(t_token ***token, int *i_token, t_cmd_len ***len)
{
	if (*i_token > 0)
	{
		(**token)->data[*i_token] = '\0';
		(**token)->next = token_init_01(*len);
		**token = (**token)->next;
		*i_token = 0;
	}
}

void	assign_token(t_token ***token, int *i_token, char input, t_cmd_len ***len)
{
	(**token)->data[*i_token] = input;
	*i_token += 1;
	(**token)->data[*i_token] = '\0';
	*i_token = 0;
	(**token)->next = token_init_01(*len);
	**token = (**token)->next;
}

int	assign_general(t_token **token, int *i_token, int char_type, char input, t_cmd_len **len)
{
	int	status = STATE_GENERAL;

	if (char_type == CHAR_QOUTE)
		status = chstatus_start(*token, &(*i_token), input, STATE_IN_QUOTE);
	else if (char_type == CHAR_DQOUTE)
		status = chstatus_start(*token, &(*i_token), input, STATE_IN_DQUOTE);
	else if (char_type == CHAR_GENERAL)
		status = chstatus_start(*token, &(*i_token), input, STATE_GENERAL);
	else if (char_type == CHAR_WHITESPACE)
		check_return_status(&token, i_token, &len);
	else if (char_type == CHAR_PIPE || char_type == CHAR_GREATER || char_type == CHAR_LESSER)
	{
		check_return_status(&token, i_token, &len);
		assign_token(&token, i_token, input, &len);
	}
	return (status);
}

t_cmd_len	*cmd_list_new()
{
	t_cmd_len	*new;

	new = (t_cmd_len *)malloc(sizeof(t_cmd_len));
	if (new == NULL)
		exit(1);
	new->len = 0;
	new->stauts = STATE_GENERAL;
	new->next = NULL;
	return (new);
}

t_cmd_len	*len_until_space(char *input, t_cmd_len *len)
{
	int	i;
	int	char_type;
	t_cmd_len	*res;

	len = cmd_list_new();
	res = len;
	i = 0;
	while (input[i] != '\0')
	{
		char_type = get_char_type_01(input[i]);
		if (len->stauts == STATE_GENERAL)
		{
			if (char_type == CHAR_QOUTE)
			{
				len->len += 1;
				len->stauts = STATE_IN_QUOTE;
			}
			else if (char_type == CHAR_DQOUTE)
			{
				len->len += 1;
				len->stauts = STATE_IN_DQUOTE;
			}
			else if (char_type == CHAR_GENERAL)
				len->len += 1;
			else if (char_type == CHAR_WHITESPACE)
			{
				if (len->len > 0)
				{
					len->next = cmd_list_new();
					len = len->next;
				}
			}
			else if (char_type == CHAR_PIPE || char_type == CHAR_GREATER || char_type == CHAR_LESSER)
			{
				len->len += 1;
				len->next = cmd_list_new();
				len = len->next;
			}
		}
		else if (len->stauts == STATE_IN_QUOTE)
		{
			len->len += 1;
			if (char_type == CHAR_QOUTE)
				len->stauts = STATE_GENERAL;
		}
		else if (len->stauts == STATE_IN_DQUOTE)
		{
			len->len += 1;
			if (char_type == CHAR_DQOUTE)
				len->stauts = STATE_GENERAL;
		}
		i += 1;
	}
	return (res);
}

void	lexer_build(char *input, t_lexer *lexerbuf)
{
	int 		i_input;
	int			i_token;
	int 		status;
	int			char_type;
	t_cmd_len	*len;
	t_token 	*token;

	i_input = 0;
	i_token = 0;
	len = len_until_space(input, len);
	token = token_init_01(&len);
	lexerbuf->list_token = token;
	status = STATE_GENERAL;
	while (input[i_input] != '\0')
	{
		char_type = get_char_type_01(input[i_input]);
		if (char_type == CHAR_PIPE)
			lexerbuf->num_token += 1;
		if (status == STATE_GENERAL)
			status = assign_general(&token, &i_token, char_type, input[i_input], &len);
		else if (status == STATE_IN_QUOTE)
			status = chstatus_end(token, &i_token, input[i_input], char_type, STATE_IN_QUOTE);
		else if (status == STATE_IN_DQUOTE)
			status = chstatus_end(token, &i_token, input[i_input], char_type, STATE_IN_DQUOTE);
		i_input += 1;
	}
	token->data[i_token] = '\0';
}
