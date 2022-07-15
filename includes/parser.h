#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include "minishell.h"

typedef struct s_redirect	t_redirect;
typedef struct	s_redirect
{
	char		*file_name;
	int			redirect_type;
	t_redirect	*next;
}	t_redirect;

typedef struct s_cmd	t_cmd;
typedef struct s_cmd
{
	t_list		*args;
	char		*heredocend;
	int			fd_out;
	int			fd_in;
	t_redirect	*redirect;
	t_cmd		*next;
}	t_cmd;

t_cmd		*lex_pars(char *input, t_cmd *cmd_list);
t_cmd		*cmd_new(void );
t_redirect	*redirect_new(void );
void		print_pars(t_cmd *cmd_list);

#endif // !PARSER_H
