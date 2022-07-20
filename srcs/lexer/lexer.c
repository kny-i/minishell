#include "minishell.h"

int	get_char_type(char c)
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
	else if (c == '>')
		res = CHAR_GREATER;
	else if (c == '<')
		res = CHAR_LESSER;
	else
		res = CHAR_GENERAL;
	return (res);
}

int	chstatus_end(t_token *token, char *input, int char_type, int status)
{
	char	*str;

	str = ft_substr(input, 0, 1);
	token->data = for_free(ft_strjoin(token->data, str), token->data);
	free(str);
	if (char_type == CHAR_QOUTE && status == STATE_IN_QUOTE)
		return (STATE_GENERAL);
	else if (char_type == CHAR_DQOUTE && status == STATE_IN_DQUOTE)
		return (STATE_GENERAL);
	return (status);
}

static int	print_lexer_error(char *str)
{
	printf("syntax error near unexpected token `%s\'\n", str);
	g_signal.exit_status = 258;
	g_signal.is_finished = true;
	return (0);
}

int	check_status(int char_type, int status)
{
	if (char_type == CHAR_GREATER || char_type == CHAR_LESSER)
		return (print_lexer_error("newline"));
	else if (char_type == CHAR_PIPE)
		return (print_lexer_error("|"));
	if (status == STATE_IN_DQUOTE)
		return (print_lexer_error("\""));
	else if (status == STATE_IN_QUOTE)
		return (print_lexer_error("\'"));
	return (1);
}

int	lexer_build(char *input, t_token **lexerbuf)
{
	int			status;
	int			char_type;
	char		*input_tmp;
	t_token		*token;

	token = token_new();
	*lexerbuf = token;
	status = STATE_GENERAL;
	while (*input)
	{
		char_type = get_char_type(*input);
		if (status == STATE_GENERAL)
			status = assign_general(&token, input, char_type);
		else if (status == STATE_IN_QUOTE)
			status = chstatus_end(token, input, char_type, STATE_IN_QUOTE);
		else if (status == STATE_IN_DQUOTE)
			status = chstatus_end(token, input, char_type, STATE_IN_DQUOTE);
		input++;
	}
	return (check_status(char_type, status));
}
