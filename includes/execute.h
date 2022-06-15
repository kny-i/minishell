#ifndef EXECUTE_H
#define EXECUTE_H

# include "./minishell.h"
# include "./lexer.h"
# include "./env.h"
# include "./parser.h"
typedef struct s_cmd	t_cmd;
typedef struct s_envp    t_envp;

typedef struct s_lexer	t_lexer;
void execute(t_cmd **cmd, t_envp *env);
int count_cmd(t_cmd *cmd);
#endif