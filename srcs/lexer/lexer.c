#include "minishell.h"
#include "lexer.h"

int	get_char_type(char c)
{
	char	res;
	if (c == CHAR_QOUTE)
		res = CHAR_QOUTE;
	else if (c == CHAR_DQOUTE)
		res = CHAR_DQOUTE;
	else if (c == CHAR_PIPE)
		res = CHAR_PIPE;
	else if (c == CHAR_AMPERSAND)
		res = CHAR_AMPERSAND;
	else if (c == CHAR_WHITESPACE)
		res = CHAR_WHITESPACE;
	else if (c == CHAR_SEMICOLON)
		res = CHAR_SEMICOLON;
	else if (c == CHAR_ESCAPESEQUENCE)
		res = CHAR_ESCAPESEQUENCE;
	else if (c == CHAR_TAB)
		res = CHAR_TAB;
	else if (c == CHAR_NEWLINE)
		res = CHAR_NEWLINE;
	else if (c == CHAR_GREATER)
		res = CHAR_GREATER;
	else if (c == CHAR_LESSER)
		res = CHAR_LESSER;
	else if (c == CHAR_NULL)
		res = CHAR_NULL;
	else
		res = CHAR_GENERAL;
	return (res);
}

void	token_init(t_token *token, int datasize)
{
	token->data = malloc(datasize + 1);
	if (token->data == NULL)
		exit(1);
	token->data[0] = 0;
	token->type = CHAR_NULL;
	token->next = NULL;
}

/*
int	lexer_build(char *input, int size, t_lexer *lexerbuf)
{
	t_token	*token;
	char	*tmp;

	if (lexerbuf == NULL)

	
}*/


int	lexer_build(char *input, int size, t_lexer *lexerbuf)
{
	t_token	*token;
	
	if (lexerbuf == NULL)
		return (-1);
	if (size == 0)
	{
		lexerbuf->num_token = 0;
		return (0);
	}
	lexerbuf->list_token = malloc(sizeof(t_token));
	if (lexerbuf->list_token == NULL)
		exit(1);
	token = lexerbuf->list_token;
	token_init(token, size);

	int	i = 0, j = 0, num_tem_token = 0;
	char	c;
	int		state = STATE_GENERAL;

	
	do
	{
		c = input[i];
		int	char_type = get_char_type(c);
/*		if (state == STATE_GENERAL)
		{
			if  (char_type == CHAR_QOUTE)
			{
				state = STATE_IN_QUOTE;
				token->data[j++] = CHAR_QOUTE;
				token->type = TOKEN;
			}
			else if (char_type == CHAR_DQOUTE)
			{
				state = STATE_IN_DQUOTE;
				token->data[j++] = CHAR_DQOUTE;
				token->type = TOKEN;
			}
			else if (char_type == CHAR_ESCAPESEQUENCE)
			{
				token->data[j++] = input[++i];
				token->type = TOKEN;
			}
			else if (char_type == CHAR_GENERAL)
			{
				token->data[j++] = c;
				token->type = TOKEN;
			}
			else if (char_type == CHAR_WHITESPACE)
			{
				if (j > 0)
				{
					token->data[j] = 0;
					token->next = malloc(sizeof(t_token));
					token = token->next;
					token_init(token, size - i);
					j = 0;
				}
			}
			else if (char_type != CHAR_NEWLINE || char_type != CHAR_NULL || char_type != CHAR_TAB)
			{
				if (j > 0)
				{
					token->data[j] = 0;
					token->next = malloc(sizeof(t_token));
					token = token->next;
					token_init(token, size - i);
					j = 0;
				}
				token->data[0] = char_type;
				token->data[1] = 0;
				token->type = char_type;
				token->next = malloc(sizeof(t_token));
				token = token->next;
				token_init(token, size - i);
			}
		}*/
		if (state == STATE_GENERAL)
		{
//			switch (char_type) 
//			{
				if (char_type == CHAR_QOUTE)
				{
					state = STATE_IN_QUOTE;
					token->data[j++] = CHAR_QOUTE;
					token->type = TOKEN;
//					break;
				}
					
				else if (char_type == CHAR_DQOUTE)
				{
					state = STATE_IN_DQUOTE;
					token->data[j++] = CHAR_DQOUTE;
					token->type = TOKEN;
				//	break;
				}
					
				else if (char_type == CHAR_ESCAPESEQUENCE)
				{
					token->data[j++] = input[++i];
					token->type = TOKEN;
				//	break;
				}
					
				else if (char_type == CHAR_GENERAL)
				{
					token->data[j++] = c;
					token->type = TOKEN;
				//	break;
				}	
				else if (char_type == CHAR_WHITESPACE)
				{
					if (j > 0) {
						token->data[j] = 0;
						token->next = malloc(sizeof(t_token));
						token = token->next;
						token_init(token, size - i);
						j = 0;
					}
				//	break;
				}	
				else if (char_type == CHAR_SEMICOLON || \
				char_type == CHAR_GREATER || \
				char_type == CHAR_LESSER || \
				char_type == CHAR_AMPERSAND || \
				char_type == CHAR_PIPE)
				{
					// end the token that was being read before
					if (j > 0) {
						token->data[j] = 0;
						token->next = malloc(sizeof(t_token));
						token = token->next;
						token_init(token, size - i);
						j = 0;
					}
					
					// next token
					token->data[0] = char_type;
					token->data[1] = 0;
					token->type = char_type;
					
					token->next = malloc(sizeof(t_token));
					token = token->next;
					token_init(token, size - i);
				//	break;
				}
			//}
		}
		else if (state == STATE_IN_DQUOTE)
		{
			token->data[j++] = c;
			if (char_type == CHAR_DQOUTE)
				state = STATE_GENERAL;
		}
		else if (state == STATE_IN_QUOTE)
		{
			token->data[j++] = c;
			if (char_type == CHAR_QOUTE)
				state = STATE_GENERAL;
		}
		if (char_type == CHAR_NULL)
		{
			if (j > 0)
			{
				token->data[j] = 0;
				num_tem_token++;
				j = 0;
			}
		}
		i++;
	}while (c != '\0');
	printf("i = %d\n", i);
	t_token	*tmp = lexerbuf->list_token;
//	printf("data = %s\n", tmp->data);
	for (;tmp != NULL; tmp = tmp->next)
		printf("data = %s\n", tmp->data);
}
