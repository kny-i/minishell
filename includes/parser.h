#ifndef PARSER_H
# define PARSER_H


# include <stdio.h>
# include "lexer.h"
# include "minishell.h"

typedef struct s_cmd	t_cmd;

typedef struct s_cmd
{
	char	*cmd;
	t_list	*args;
//	char			*stdin_str;
//	t_list			*heredoc_end;
	char	*heredocend;
	int		fd_out;
	int		fd_in;
//	t_cmd	*prev;
	t_cmd	*next;
}	t_cmd;

t_cmd	*lex_pars(char *input);;
void	cmd_add_back(t_cmd **lst, t_cmd *new);
t_cmd	*cmd_new(char *cmd);

#endif // !PARSER_H