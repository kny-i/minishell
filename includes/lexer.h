#ifndef LEXER_H
# define LEXER_H

typedef enum	e_token_type
{
	CHAR_GENERAL		= -1,
	CHAR_PIPE			= '|',
	CHAR_AMPERSAND		= '&',
	CHAR_QOUTE			= '\'',
	CHAR_DQOUTE			= '\"',
	CHAR_SEMICOLON		= ';',
	CHAR_WHITESPACE		= ' ',
	CHAR_ESCAPESEQUENCE	= '\\',
	CHAR_TAB			= '\t',
	CHAR_NEWLINE		= '\n',
	CHAR_GREATER		= '>',
	CHAR_LESSER			= '<',
	CHAR_NULL			= 0,
	TOKEN				= -1,
}	t_token_type;

typedef enum	e_status
{
	STATE_IN_DQUOTE,
	STATE_IN_QUOTE,
	STATE_IN_ESCAPESEQ,
	STATE_GENERAL,
}	t_status;

typedef struct s_token	t_token;
typedef struct s_lexer	t_lexer;

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
}	t_lexer;



#endif // !LEXER_H