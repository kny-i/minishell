#ifndef EXPAND_H
# define EXPAND_H

//# include "./minishell.h"
# include "parser.h"
# include  "env.h"

bool	expand(t_cmd *cmd, t_envp *envp);

#endif