#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include "lexer.h"
# include "minishell.h"
# include "utils.h"

typedef struct	s_redirect	t_redirect;
struct	s_redirect
{
	char		*file_name;
	int			redirect_type;
	t_redirect	*next;
};

typedef struct	s_cmd t_cmd;
typedef struct	s_cmd
{
	t_list		*args;
	char		*heredocend;
	int			fd_out;
	int			fd_in;
	t_redirect	*redirect;
	t_cmd	*next;
}	t_cmd;

t_cmd		*lex_pars(char *input, t_cmd *cmd_list);
void		cmd_add_back(t_cmd **lst, t_cmd *new);
t_cmd		*cmd_new();
t_redirect	*redirect_new();


void	print_pars(t_cmd *cmd_list);

#endif // !PARSER_H
