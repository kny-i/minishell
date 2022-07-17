#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

typedef enum e_token_type
{
	CHAR_GENERAL		= -1,
	CHAR_PIPE			= '|',
	CHAR_QOUTE			= '\'',
	CHAR_DQOUTE			= '\"',
	CHAR_WHITESPACE		= ' ',
	CHAR_GREATER		= '>',
	CHAR_LESSER			= '<',
	TOKEN				= -1,
}	t_token_type;

typedef enum e_status
{
	STATE_IN_DQUOTE,
	STATE_IN_QUOTE,
	STATE_GENERAL,
}	t_status;

typedef struct s_token		t_token;
typedef struct s_lexer		t_lexer;
typedef struct s_cmd_len	t_cmd_len;

typedef struct s_cmd_len
{
	size_t		len;
	int			stauts;
	t_cmd_len	*next;
}	t_cmd_len;

typedef struct s_token
{
	char	*data;
	int		type;
	t_token	*next;
}	t_token;

typedef struct s_lexer
{
	t_token	*list_token;
	int		num_token;
}			t_lexer;

int		lexer_build(char *input, t_token **lexerbuf);
int		get_char_type(char c);

#endif // !LEXER_H