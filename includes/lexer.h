#ifndef LEXER_H
# define LEXER_H

# include <glob.h>
# include "./minishell.h"

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
	STATE_IN_ESCAPESEQ,	//<- いらない??
	STATE_GENERAL,
}	t_status;


typedef struct s_cmdline	t_cmdline;
typedef struct	s_cmdline
{
	char		*cmd;
	t_list		*cmd_args;
	t_cmdline	*next;
}	t_cmdline;



typedef struct s_token	t_token;
typedef struct s_lexer	t_lexer;

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
}	t_lexer;

int	lexer_build(char *input, int size, t_lexer *lexerbuf);


void    lexer_build_01(char *input, int size, t_lexer *lexerbuf);

#endif // !LEXER_H