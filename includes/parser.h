#ifndef PARSER_H
#define PARSER_H

#include "astree.h"
#include "lexer.h"
typedef struct s_cmd
{
	char			*cmd;
	t_list			*args;
	char			*stdin_str;
	t_list			*heredoc_end;
	int				fd_out;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}					t_cmd;

t_cmd *parse(t_lexer *lexerbuf);

#endif