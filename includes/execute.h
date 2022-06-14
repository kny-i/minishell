#ifndef EXECUTE_H
#define EXECUTE_H

# include "./minishell.h"
# include "./lexer.h"
# include "./env.h"

typedef struct s_lexer	t_lexer;
void execute(t_cmd **cmd, t_env *env);

#endif