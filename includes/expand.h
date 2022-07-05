#ifndef EXPAND_H
#define EXPAND_H

//# include "./minishell.h"
# include "parser.h"
# include  "env.h"


int 	check_redirect_out(t_cmd *cmd_list);
int     check_redirect_input(t_cmd *cmd_list);
bool    expand(t_cmd **cmd, t_envp **envp);
#endif